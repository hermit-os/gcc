// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// POSIX library calls on systems which do not use the largefile
// interface.

package syscall

//sys Fstat(fd int, stat *Stat_t) (err error)
//fstat(fd _C_int, stat *Stat_t) _C_int

func Ftruncate(fd int, length int64) (err error) {
	return ENOSYS
}

func Lstat(path string, stat *Stat_t) (err error) {
	return ENOSYS
}

//sys	mmap(addr uintptr, length uintptr, prot int, flags int, fd int, offset int64) (xaddr uintptr, err error)
//mmap(addr *byte, length Size_t, prot _C_int, flags _C_int, fd _C_int, offset Offset_t) *byte

//sys	Open(path string, mode int, perm uint32) (fd int, err error)
//__go_open(path *byte, mode _C_int, perm Mode_t) _C_int

func Pread(fd int, p []byte, offset int64) (n int, err error) {
	return 0, ENOSYS
}

func Pwrite(fd int, p []byte, offset int64) (n int, err error) {
	return 0, ENOSYS
}

//sys	Seek(fd int, offset int64, whence int) (off int64, err error)
//lseek(fd _C_int, offset Offset_t, whence _C_int) Offset_t

//sys	Stat(path string, stat *Stat_t) (err error)
//stat(path *byte, stat *Stat_t) _C_int

func Truncate(path string, length int64) (err error) {
	return ENOSYS
}
