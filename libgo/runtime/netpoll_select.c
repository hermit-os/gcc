// Copyright 2013 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// +build solaris
// +build hermit

#include "config.h"

#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/times.h>
#include <sys/types.h>
#include <fcntl.h>

#ifdef __hermit__
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>

int reschedule(void);

#define IPC_PORT	4711
#define GETFD(x)	(x & ~LWIP_FD_BIT)
#else
#define GETFD(x)	x
#endif

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#include "runtime.h"
#include "malloc.h"

static Lock selectlock;
static int rdwake;
static int wrwake;

static fd_set fds;
static PollDesc **data;
static int allocated;

void
runtime_netpollinit(void)
{
#ifdef __hermit__
	struct sockaddr_in sa_server;
	struct sockaddr_in sa_client;
	struct sockaddr_in sa_dummy;
	struct in_addr addr_local;
	struct in_addr addr_any;
	socklen_t length;
	int server;
	int reuse = 1;
#else
	int p[2];
#endif
	int fl;

	FD_ZERO(&fds);
#ifdef __hermit__
	allocated = MEMP_NUM_NETCONN;
#else
	allocated = 128;
#endif
	data = runtime_mallocgc(allocated * sizeof(PollDesc *), 0,
				FlagNoScan|FlagNoProfiling|FlagNoInvokeGC);

#ifdef __hermit__
	// HermitCore doesn't support pipes
	// => create a self-connection via sockets, at first the server side
	server = socket(PF_INET, SOCK_STREAM, 0);
	if (server < 0)
		runtime_throw("netpollinit: socket failed");

	if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
		runtime_throw("netpollinit: setsockopt failed");

	memset((char *) &sa_server, 0x00, sizeof(sa_server));
	sa_server.sin_family = AF_INET;
	sa_server.sin_port = htons(IPC_PORT);
	addr_any.s_addr = INADDR_ANY;
	sa_server.sin_addr = addr_any;

	if (bind(server, (struct sockaddr *) &sa_server, sizeof(sa_server)) < 0)
		runtime_throw("netpollinit: bind failed");

	if (listen(server, 2) != 0)
		runtime_throw("netpollinit: listen failed");

	// now the client side
	wrwake = socket(PF_INET, SOCK_STREAM, 0);
	if (wrwake < 0)
		runtime_throw("netpollinit: socket failed");

	sa_client.sin_family = AF_INET;
	sa_client.sin_port = htons(IPC_PORT);
	addr_local.s_addr = inet_addr("127.0.0.1");
	sa_client.sin_addr = addr_local;

	if (connect(wrwake, (struct sockaddr *) &sa_client, sizeof(sa_client)) < 0)
		runtime_throw("netpollinit: connect failed");

	if ((rdwake = accept(server, (struct sockaddr *) &sa_dummy, &length)) < 0)
		runtime_throw("netpollinit: accept failed");

	close(server);
#else
	if(pipe(p) < 0)
		runtime_throw("netpollinit: failed to create pipe");
	rdwake = p[0];
	wrwake = p[1];
#endif

	fl = fcntl(rdwake, F_GETFL);
	if(fl < 0)
		runtime_throw("netpollinit: fcntl failed");
	fl |= O_NONBLOCK;
	if(fcntl(rdwake, F_SETFL, fl))
		 runtime_throw("netpollinit: fcntl failed");
#ifndef __hermit__
	fcntl(rdwake, F_SETFD, FD_CLOEXEC);
#endif

	fl = fcntl(wrwake, F_GETFL);
	if(fl < 0)
		runtime_throw("netpollinit: fcntl failed");
	fl |= O_NONBLOCK;
	if(fcntl(wrwake, F_SETFL, fl))
		 runtime_throw("netpollinit: fcntl failed");
#ifndef __hermit__
	fcntl(wrwake, F_SETFD, FD_CLOEXEC);
#endif

	FD_SET(rdwake, &fds);
}

int32
runtime_netpollopen(uintptr fd, PollDesc *pd)
{
	byte b;

	runtime_lock(&selectlock);

#ifdef __hermit__
	// HermitCore has a fix limit of socket ids
	// => no resize possible
	if((int)GETFD(fd) >= allocated) {
		runtime_unlock(&selectlock);
		return -1;
	}
#else
	if((int)GETFD(fd) >= allocated) {
		int c;
		PollDesc **n;

		c = allocated;

		runtime_unlock(&selectlock);

		while((int)GETFD(fd) >= c)
			c *= 2;
		n = runtime_mallocgc(c * sizeof(PollDesc *), 0,
				     FlagNoScan|FlagNoProfiling|FlagNoInvokeGC);

		runtime_lock(&selectlock);

		if(c > allocated) {
			__builtin_memcpy(n, data, allocated * sizeof(PollDesc *));
			allocated = c;
			data = n;
		}
	}
#endif
	FD_SET(fd, &fds);
	data[GETFD(fd)] = pd;

	runtime_unlock(&selectlock);

	b = 0;
	write(wrwake, &b, sizeof b);

	return 0;
}

int32
runtime_netpollclose(uintptr fd)
{
	byte b;

	runtime_lock(&selectlock);

	FD_CLR(fd, &fds);
	data[GETFD(fd)] = nil;

	runtime_unlock(&selectlock);

	b = 0;
	write(wrwake, &b, sizeof b);

	return 0;
}

/* Used to avoid using too much stack memory.  */
static bool inuse;
static fd_set grfds, gwfds, gefds, gtfds;

G*
runtime_netpoll(bool block)
{
	fd_set *prfds, *pwfds, *pefds, *ptfds;
	bool allocatedfds;
	struct timeval timeout;
	struct timeval *pt;
	int max, c, i;
	G *gp;
	int32 mode;
	byte b;
	struct stat st;

	allocatedfds = false;

 retry:
	runtime_lock(&selectlock);

	max = allocated;

	if(max == 0) {
		runtime_unlock(&selectlock);
		return nil;
	}

	if(inuse) {
		if(!allocatedfds) {
			prfds = runtime_SysAlloc(4 * sizeof fds, &mstats.other_sys);
			pwfds = prfds + 1;
			pefds = pwfds + 1;
			ptfds = pefds + 1;
			allocatedfds = true;
		}
	} else {
		prfds = &grfds;
		pwfds = &gwfds;
		pefds = &gefds;
		ptfds = &gtfds;
		inuse = true;
		allocatedfds = false;
	}

	__builtin_memcpy(prfds, &fds, sizeof fds);

	runtime_unlock(&selectlock);

	__builtin_memcpy(pwfds, prfds, sizeof fds);
	FD_CLR(rdwake, pwfds);
	__builtin_memcpy(pefds, pwfds, sizeof fds);

	__builtin_memcpy(ptfds, pwfds, sizeof fds);

	__builtin_memset(&timeout, 0, sizeof timeout);
	pt = &timeout;
	if(block)
		pt = nil;

	c = select(max, prfds, pwfds, pefds, pt);
	if(c < 0) {
		if(errno == EBADF) {
			// Some file descriptor has been closed.
			// Check each one, and treat each closed
			// descriptor as ready for read/write.
			c = 0;
			FD_ZERO(prfds);
			FD_ZERO(pwfds);
			FD_ZERO(pefds);
			for(i = 0; i < max; i++) {
				if(FD_ISSET(i, ptfds)
				   && fstat(i, &st) < 0
				   && errno == EBADF) {
					FD_SET(i, prfds);
					FD_SET(i, pwfds);
					c += 2;
				}
			}
		}
		else {
			if(errno != EINTR)
				runtime_printf("runtime: select failed with %d\n", errno);
			goto retry;
		}
	}
	gp = nil;
	for(i = 0; i < max && c > 0; i++) {
		mode = 0;
		if(FD_ISSET(i, prfds)) {
			mode += 'r';
			--c;
		}
		if(FD_ISSET(i, pwfds)) {
			mode += 'w';
			--c;
		}
		if(FD_ISSET(i, pefds)) {
			mode = 'r' + 'w';
			--c;
		}
#ifdef __hermit__
		if((i|LWIP_FD_BIT) == rdwake && mode != 0) {
#else
		if(i == rdwake && mode != 0) {
#endif
			while(read(rdwake, &b, sizeof b) > 0)
				;
			continue;
		}
		if(mode) {
			PollDesc *pd;

			runtime_lock(&selectlock);
			pd = data[i];
			runtime_unlock(&selectlock);
			if(pd != nil)
				runtime_netpollready(&gp, pd, mode);
		}
	}
#ifdef __hermit__
	// on a tickless system (e.g. HermitCore), we have to reschedule
	// to consume the message
	reschedule();
#endif
	if(block && gp == nil)
		goto retry;

	if(allocatedfds) {
		runtime_SysFree(prfds, 4 * sizeof fds, &mstats.other_sys);
	} else {
		runtime_lock(&selectlock);
		inuse = false;
		runtime_unlock(&selectlock);
	}

	return gp;
}

void
runtime_netpoll_scan(struct Workbuf** wbufp, void (*enqueue1)(struct Workbuf**, Obj))
{
	enqueue1(wbufp, (Obj){(byte*)&data, sizeof data, 0});
}
