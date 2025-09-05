// Copyright 2025 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build hermit

package runtime

import (
	"unsafe"
)

//extern malloc
func libc_malloc(uintptr) unsafe.Pointer

//extern sys_get_processor_count
func sys_get_processor_count() uint

//extern sys_getpagesize
func sys_getpagesize() int32

//extern sys_getpid
func sys_getpid() _pid_t

func getpid() _pid_t {
	return sys_getpid();
}

//go:noescape
//extern sem_init
func sem_init(sem *semt, pshared int32, value uint32) int32

//go:noescape
//extern sem_wait
func sem_wait(sem *semt) int32

//go:noescape
//extern sem_post
func sem_post(sem *semt) int32

//go:noescape
//extern sem_timedwait
func sem_timedwait(sem *semt, timeout *timespec) int32

//go:noescape
//extern clock_gettime
func clock_gettime(clock_id int64, timeout *timespec) int32

//go:nosplit
func semacreate(mp *m) {
	if mp.waitsema != 0 {
		return
	}

	var sem *semt

	sem = (*semt)(libc_malloc(unsafe.Sizeof(*sem)))
	if sem_init(sem, 0, 0) != 0 {
		throw("sem_init")
	}
	mp.waitsema = uintptr(unsafe.Pointer(sem))
}

//go:nosplit
func semasleep(ns int64) int32 {
	mp := getg().m
	if ns >= 0 {
		var ts timespec

		if clock_gettime(_CLOCK_REALTIME, &ts) != 0 {
			throw("clock_gettime")
		}

		sec := int64(ts.tv_sec) + ns/1e9
		nsec := int64(ts.tv_nsec) + ns%1e9
		if nsec >= 1e9 {
			sec++
			nsec -= 1e9
		}
		if sec != int64(timespec_sec_t(sec)) {
			// Handle overflows (timespec_sec_t is 32-bit in 32-bit applications)
			sec = 1<<31 - 1
		}
		ts.tv_sec = timespec_sec_t(sec)
		ts.tv_nsec = timespec_nsec_t(nsec)

		if sem_timedwait((*semt)(unsafe.Pointer(mp.waitsema)), &ts) != 0 {
			err := errno()
			if err == _ETIMEDOUT || err == _EAGAIN || err == _EINTR {
				return -1
			}
			println("sem_timedwait err ", err, " ts.tv_sec ", ts.tv_sec, " ts.tv_nsec ", ts.tv_nsec, " ns ", ns, " id ", mp.id)
			throw("sem_timedwait")
		}
		return 0
	}
	for {
		r1 := sem_wait((*semt)(unsafe.Pointer(mp.waitsema)))
		if r1 == 0 {
			break
		}
		if errno() == _EINTR {
			continue
		}
		throw("sem_wait")
	}
	return 0
}

//go:nosplit
func semawakeup(mp *m) {
	if sem_post((*semt)(unsafe.Pointer(mp.waitsema))) != 0 {
		throw("sem_post")
	}
}

//go:nosplit
func sigsave(p *sigset) {
}

//go:nosplit
func msigrestore(sigmask sigset) {
}

//go:nosplit
//go:nowritebarrierrec
func clearSignalHandlers() {
}

//go:nosplit
func sigblock(exiting bool) {
}

func initsig(preinit bool) {
}

type mOS struct {
	waitsema uintptr // semaphore for parking on locks
}

func getProcID() uint64 {
	return uint64(sys_getpid())
}

func setProcessCPUProfiler(hz int32) {}
func setThreadCPUProfiler(hz int32)  {}
func sigdisable(uint32)              {}
func sigenable(uint32)               {}
func sigignore(uint32)               {}
func minitSignals()                  {}
func unminitSignals()                {}

const preemptMSupported = false

func preemptM(mp *m) {
	// No threads, so nothing to do.
}

func signame(sig uint32) string {
	return ""
}

func crash() {
	*(*int32)(nil) = 0
}

func osinit() {
	ncpu = int32(sys_get_processor_count())
	physPageSize = uintptr(sys_getpagesize())
}
