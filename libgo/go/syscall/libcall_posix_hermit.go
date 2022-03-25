// Copyright 2011 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// POSIX library calls.
// This file is compiled as ordinary Go code,
// but it is also input to mksyscall,
// which parses the //sys lines and generates library call stubs.
// Note that sometimes we use a lowercase //sys name and
// wrap it in our own nicer implementation.

package syscall

import "unsafe"

/*
 * Wrapped
 */

func pipe(p *[2]_C_int) (err error) {
	return ENOSYS
}

func Pipe(p []int) (err error) {
	if len(p) != 2 {
		return EINVAL
	}
	var pp [2]_C_int
	err = pipe(&pp)
	p[0] = int(pp[0])
	p[1] = int(pp[1])
	return
}

func utimes(path string, times *[2]Timeval) (err error) {
	return ENOSYS
}

func Utimes(path string, tv []Timeval) (err error) {
	if len(tv) != 2 {
		return EINVAL
	}
	return utimes(path, (*[2]Timeval)(unsafe.Pointer(&tv[0])))
}

func getcwd(buf *byte, size Size_t) (err error) {
	return EINVAL
}

const ImplementsGetwd = true

func Getwd() (ret string, err error) {
	for len := Size_t(4096); ; len *= 2 {
		b := make([]byte, len)
		err := getcwd(&b[0], len)
		if err == nil {
			i := 0
			for b[i] != 0 {
				i++
			}
			return string(b[0:i]), nil
		}
		if err != ERANGE {
			return "", err
		}
	}
}

func Getcwd(buf []byte) (n int, err error) {
	err = getcwd(&buf[0], Size_t(len(buf)))
	if err == nil {
		i := 0
		for buf[i] != 0 {
			i++
		}
		n = i + 1
	}
	return
}

func getgroups(size int, list *Gid_t) (nn int, err error) {
	return 0, ENOSYS
}

func Getgroups() (gids []int, err error) {
	n, err := getgroups(0, nil)
	if err != nil {
		return nil, err
	}
	if n == 0 {
		return nil, nil
	}

	// Sanity check group count.  Max is 1<<16 on GNU/Linux.
	if n < 0 || n > 1<<20 {
		return nil, EINVAL
	}

	a := make([]Gid_t, n)
	n, err = getgroups(n, &a[0])
	if err != nil {
		return nil, err
	}
	gids = make([]int, n)
	for i, v := range a[0:n] {
		gids[i] = int(v)
	}
	return
}

func setgroups(n int, list *Gid_t) (err error) {
	return ENOSYS
}

func Setgroups(gids []int) (err error) {
	if len(gids) == 0 {
		return setgroups(0, nil)
	}

	a := make([]Gid_t, len(gids))
	for i, v := range gids {
		a[i] = Gid_t(v)
	}
	return setgroups(len(a), &a[0])
}

type WaitStatus uint32

// The WaitStatus methods are implemented in C, to pick up the macros
// #defines in <sys/wait.h>.

func (w WaitStatus) Exited() bool
func (w WaitStatus) Signaled() bool
func (w WaitStatus) Stopped() bool
func (w WaitStatus) Continued() bool
func (w WaitStatus) CoreDump() bool
func (w WaitStatus) ExitStatus() int
func (w WaitStatus) Signal() Signal
func (w WaitStatus) StopSignal() Signal
func (w WaitStatus) TrapCause() int

func Mkfifo(path string, mode uint32) (err error) {
	return ENOSYS
}

//sys	Select(nfd int, r *FdSet, w *FdSet, e *FdSet, timeout *Timeval) (n int, err error)
//select(nfd _C_int, r *FdSet, w *FdSet, e *FdSet, timeout *Timeval) _C_int

const nfdbits = int(unsafe.Sizeof(fds_bits_type(0)) * 8)

type FdSet struct {
	Bits [(FD_SETSIZE + nfdbits - 1) / nfdbits]fds_bits_type
}

func FDSet(fd int, set *FdSet) {
	set.Bits[fd/nfdbits] |= (1 << (uint)(fd%nfdbits))
}

func FDClr(fd int, set *FdSet) {
	set.Bits[fd/nfdbits] &^= (1 << (uint)(fd%nfdbits))
}

func FDIsSet(fd int, set *FdSet) bool {
	if set.Bits[fd/nfdbits]&(1<<(uint)(fd%nfdbits)) != 0 {
		return true
	} else {
		return false
	}
}

func FDZero(set *FdSet) {
	for i := range set.Bits {
		set.Bits[i] = 0
	}
}

func Access(path string, mode uint32) (err error) {
	return ENOSYS
}

func Chdir(path string) (err error) {
	return ENOSYS
}

func Chmod(path string, mode uint32) (err error) {
	return ENOSYS
}

func Chown(path string, uid int, gid int) (err error) {
	return ENOSYS
}

func Chroot(path string) (err error) {
	return ENOSYS
}

//sys	Close(fd int) (err error)
//close(fd _C_int) _C_int

func Creat(path string, mode uint32) (fd int, err error) {
	return 0, ENOSYS
}

func Dup(oldfd int) (fd int, err error) {
	return 0, ENOSYS
}

func Dup2(oldfd int, newfd int) (err error) {
	return ENOSYS
}

//sys	Exit(code int)
//exit(code _C_int)

//sys	fcntl(fd int, cmd int, arg int) (val int, err error)
//__go_fcntl(fd _C_int, cmd _C_int, arg _C_int) _C_int

func Fdatasync(fd int) (err error) {
	return ENOSYS
}

func Fsync(fd int) (err error) {
	return ENOSYS
}

func Fchdir(fd int) (err error) {
	return ENOSYS
}

func Fchmod(fd int, mode uint32) (err error) {
	return ENOSYS
}

func Fchown(fd int, uid int, gid int) (err error) {
	return ENOSYS
}

func Getegid() (egid int) {
	return 0
}

func Geteuid() (euid int) {
	return 0
}

func Getgid() (gid int)  {
	return 0
}

//sysnb	Getpagesize() (pagesize int)
//getpagesize() _C_int

//sysnb	Getpid() (pid int)
//getpid() Pid_t

func Getppid() (ppid int) {
	return 0;
}

//sysnb	gettimeofday(tv *Timeval, tz *byte) (err error)
//gettimeofday(tv *Timeval, tz *byte) _C_int
func Gettimeofday(tv *Timeval) (err error) {
	return gettimeofday(tv, nil)
}

func Getuid() (uid int) {
	return 0
}

//sysnb	Kill(pid int, sig Signal) (err error)
//kill(pid Pid_t, sig _C_int) _C_int

func Lchown(path string, uid int, gid int) (err error) {
	return ENOSYS
}

//sys	Link(oldpath string, newpath string) (err error)
//link(oldpath *byte, newpath *byte) _C_int

func Mkdir(path string, mode uint32) (err error) {
	return ENOSYS
}

//sys	read(fd int, p []byte) (n int, err error)
//read(fd _C_int, buf *byte, count Size_t) Ssize_t

//sys	readlen(fd int, p *byte, np int) (n int, err error)
//read(fd _C_int, buf *byte, count Size_t) Ssize_t

func Readlink(path string, buf []byte) (n int, err error) {
	return 0, ENOSYS
}

func Rename(oldpath string, newpath string) (err error) {
	return ENOSYS
}

func Rmdir(path string) (err error) {
	return ENOSYS
}

func Settimeofday(tv *Timeval) (err error) {
	return ENOSYS
}

func Symlink(oldpath string, newpath string) (err error) {
	return ENOSYS
}

func Setuid(uid int) (err error) {
	return ENOSYS
}

//sysnb	Time(t *Time_t) (tt Time_t, err error)
//time(t *Time_t) Time_t

//sysnb	Times(tms *Tms) (ticks uintptr, err error)
//times(tms *Tms) _clock_t

//sys	Unlink(path string) (err error)
//unlink(path *byte) _C_int

//sys	write(fd int, p []byte) (n int, err error)
//write(fd _C_int, buf *byte, count Size_t) Ssize_t

//sys	writelen(fd int, p *byte, np int) (n int, err error)
//write(fd _C_int, buf *byte, count Size_t) Ssize_t

func TimespecToNsec(ts Timespec) int64 { return int64(ts.Sec)*1e9 + int64(ts.Nsec) }

func NsecToTimespec(nsec int64) (ts Timespec) {
	ts.Sec = Timespec_sec_t(nsec / 1e9)
	ts.Nsec = Timespec_nsec_t(nsec % 1e9)
	return
}

func TimevalToNsec(tv Timeval) int64 { return int64(tv.Sec)*1e9 + int64(tv.Usec)*1e3 }

func NsecToTimeval(nsec int64) (tv Timeval) {
	nsec += 999 // round up to microsecond
	tv.Sec = Timeval_sec_t(nsec / 1e9)
	tv.Usec = Timeval_usec_t(nsec % 1e9 / 1e3)
	return
}
