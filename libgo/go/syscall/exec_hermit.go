// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build hermit

// Fork, exec, wait, etc.

package syscall

import (
	"sync"
)

// Lock synchronizing creation of new file descriptors with fork.
//
// We want the child in a fork/exec sequence to inherit only the
// file descriptors we intend. To do that, we mark all file
// descriptors close-on-exec and then, in the child, explicitly
// unmark the ones we want the exec'ed program to keep.
// Unix doesn't make this easy: there is, in general, no way to
// allocate a new file descriptor close-on-exec. Instead you
// have to allocate the descriptor and then mark it close-on-exec.
// If a fork happens between those two events, the child's exec
// will inherit an unwanted file descriptor.
//
// This lock solves that race: the create new fd/mark close-on-exec
// operation is done holding ForkLock for reading, and the fork itself
// is done holding ForkLock for writing. At least, that's the idea.
// There are some complications.
//
// Some system calls that create new file descriptors can block
// for arbitrarily long times: open on a hung NFS server or named
// pipe, accept on a socket, and so on. We can't reasonably grab
// the lock across those operations.
//
// It is worse to inherit some file descriptors than others.
// If a non-malicious child accidentally inherits an open ordinary file,
// that's not a big deal. On the other hand, if a long-lived child
// accidentally inherits the write end of a pipe, then the reader
// of that pipe will not see EOF until that child exits, potentially
// causing the parent program to hang. This is a common problem
// in threaded C programs that use popen.
//
// Luckily, the file descriptors that are most important not to
// inherit are not the ones that can take an arbitrarily long time
// to create: pipe returns instantly, and the net package uses
// non-blocking I/O to accept on a listening socket.
// The rules for which file descriptor-creating operations use the
// ForkLock are as follows:
//
// 1) Pipe. Does not block. Use the ForkLock.
// 2) Socket. Does not block. Use the ForkLock.
// 3) Accept. If using non-blocking mode, use the ForkLock.
//             Otherwise, live with the race.
// 4) Open. Can block. Use O_CLOEXEC if available (GNU/Linux).
//             Otherwise, live with the race.
// 5) Dup. Does not block. Use the ForkLock.
//             On GNU/Linux, could use fcntl F_DUPFD_CLOEXEC
//             instead of the ForkLock, but only for dup(fd, -1).

var ForkLock sync.RWMutex

//sysnb	raw_fork() (pid Pid_t, err Errno)
//fork() Pid_t

//sysnb	raw_getpid() (pid Pid_t)
//getpid() Pid_t

//sysnb	raw_getppid() (pid Pid_t)
//getppid() Pid_t

//sysnb raw_setsid() (err Errno)
//setsid() Pid_t

//sysnb raw_setpgid(pid int, pgid int) (err Errno)
//setpgid(pid Pid_t, pgid Pid_t) _C_int

//sysnb	raw_chroot(path *byte) (err Errno)
//chroot(path *byte) _C_int

//sysnb	raw_chdir(path *byte) (err Errno)
//chdir(path *byte) _C_int

//sysnb	raw_fcntl(fd int, cmd int, arg int) (val int, err Errno)
//__go_fcntl(fd _C_int, cmd _C_int, arg _C_int) _C_int

//sysnb	raw_close(fd int) (err Errno)
//close(fd _C_int) _C_int

//sysnb	raw_ioctl(fd int, cmd uintptr, val int) (rval int, err Errno)
//__go_ioctl(fd _C_int, cmd _C_int, val _C_int) _C_int

//sysnb raw_ioctl_ptr(fd int, cmd uintptr, val unsafe.Pointer) (rval int, err Errno)
//__go_ioctl_ptr(fd _C_int, cmd _C_int, val unsafe.Pointer) _C_int

//sysnb	raw_execve(argv0 *byte, argv **byte, envv **byte) (err Errno)
//execve(argv0 *byte, argv **byte, envv **byte) _C_int

//sysnb raw_read(fd int, buf *byte, count int) (c int, err Errno)
//read(fd _C_int, buf *byte, count Size_t) Ssize_t

//sysnb	raw_write(fd int, buf *byte, count int) (c int, err Errno)
//write(fd _C_int, buf *byte, count Size_t) Ssize_t

//sysnb	raw_exit(status int)
//_exit(status _C_int)

//sysnb raw_dup2(oldfd int, newfd int) (err Errno)
//dup2(oldfd _C_int, newfd _C_int) _C_int

//sysnb raw_dup3(oldfd int, newfd int, flags int) (err Errno)
//dup3(oldfd _C_int, newfd _C_int, flags _C_int) _C_int

//sysnb raw_kill(pid Pid_t, sig Signal) (err Errno)
//kill(pid Pid_t, sig _C_int) _C_int

//sysnb raw_setgroups(size int, list unsafe.Pointer) (err Errno)
//setgroups(size Size_t, list *Gid_t) _C_int

func CloseOnExec(fd int) { fcntl(fd, F_SETFD, FD_CLOEXEC) }

func SetNonblock(fd int, nonblocking bool) (err error) {
	flag, err := fcntl(fd, F_GETFL, 0)
	if err != nil {
		return err
	}
	if nonblocking {
		flag |= O_NONBLOCK
	} else {
		flag &^= O_NONBLOCK
	}
	_, err = fcntl(fd, F_SETFL, flag)
	return err
}

func ForkExec(argv0 string, argv []string, envv []string, dir string, fd []int) (pid int, err error) {
	return -1, ENOSYS
}

func Exec(argv0 string, argv []string, envv []string) (err error) {
	return ENOSYS
}