// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build hermit

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

// Do the interface allocations only once for common
// Errno values.
var (
	errEAGAIN error = EAGAIN
	errEINVAL error = EINVAL
	errENOENT error = ENOENT
)

// errnoErr returns common boxed Errno values, to prevent
// allocations at runtime.
func errnoErr(e Errno) error {
	switch e {
	case 0:
		return nil
	case EAGAIN:
		return errEAGAIN
	case EINVAL:
		return errEINVAL
	case ENOENT:
		return errENOENT
	}
	return e
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
	if asanenabled && n > 0 {
		asanWrite(unsafe.Pointer(&p[0]), n)
	}
	return
}

func Write(fd int, p []byte) (n int, err error) {
	if race.Enabled {
		race.ReleaseMerge(unsafe.Pointer(&ioSync))
	}
	if faketime && (fd == 1 || fd == 2) {
		n = faketimeWrite(fd, p)
		if n < 0 {
			n, err = 0, errnoErr(Errno(-n))
		}
	} else {
		n, err = write(fd, p)
	}
	if race.Enabled && n > 0 {
		race.ReadRange(unsafe.Pointer(&p[0]), n)
	}
	if msanenabled && n > 0 {
		msanRead(unsafe.Pointer(&p[0]), n)
	}
	if asanenabled && n > 0 {
		asanRead(unsafe.Pointer(&p[0]), n)
	}
	return
}

var ioSync int64
