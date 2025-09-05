// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build hermit
// +build hermit

package os

import (
	"syscall"
)

// FIXME: pathconf returns long, not int.
//extern pathconf
func libc_pathconf(*byte, int32) int

func direntType(*syscall.Dirent) byte

func clen(n []byte) int {
	for i := 0; i < len(n); i++ {
		if n[i] == 0 {
			return i
		}
	}
	return len(n)
}

func (f *File) readdir(n int, mode readdirMode) (names []string, dirents []DirEntry, infos []FileInfo, err error) {
	return nil, nil, nil, syscall.ENOSYS
}
