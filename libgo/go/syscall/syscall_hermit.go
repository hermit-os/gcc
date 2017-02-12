// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// +build darwin dragonfly freebsd linux netbsd openbsd solaris

package syscall

import (
	"internal/race"
	"unsafe"
)

var (
	Stdin  = 0
	Stdout = 1
	Stderr = 2
)

// workaround for the missing declaration
const O_SYNC = 0x0040

func Syscall(trap, a1, a2, a3 uintptr) (r1, r2, err uintptr) {
	z := -1
	return uintptr(z), 0, uintptr(ENOSYS)
}

func Syscall6(trap, a1, a2, a3, a4, a5, a6 uintptr) (r1, r2, err uintptr) {
	z := -1
	return uintptr(z), 0, uintptr(ENOSYS)
}

func RawSyscall(trap, a1, a2, a3 uintptr) (r1, r2, err uintptr) {
	z := -1
	return uintptr(z), 0, uintptr(ENOSYS)
}

func RawSyscall6(trap, a1, a2, a3, a4, a5, a6 uintptr) (r1, r2, err uintptr) {
	z := -1
	return uintptr(z), 0, uintptr(ENOSYS)
}

// A Signal is a number describing a process signal.
// It implements the os.Signal interface.
type Signal int

func (s Signal) Signal() {}

func Signame(s Signal) string

func (s Signal) String() string {
	return Signame(s)
}

func Read(fd int, p []byte) (n int, err error) {
	n, err = read(fd, p)
	if race.Enabled {
		if n > 0 {
			race.WriteRange(unsafe.Pointer(&p[0]), n)
		}
		if err == nil {
			race.Acquire(unsafe.Pointer(&ioSync))
		}
	}
	if msanenabled && n > 0 {
		msanWrite(unsafe.Pointer(&p[0]), n)
	}
	return
}

func Write(fd int, p []byte) (n int, err error) {
	if race.Enabled {
		race.ReleaseMerge(unsafe.Pointer(&ioSync))
	}
	n, err = write(fd, p)
	if race.Enabled && n > 0 {
		race.ReadRange(unsafe.Pointer(&p[0]), n)
	}
	if msanenabled && n > 0 {
		msanRead(unsafe.Pointer(&p[0]), n)
	}
	return
}

var ioSync int64
