// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build hermit

package os

import "syscall"

// Pipe returns a connected pair of Files; reads from r return bytes written to w.
// It returns the files and an error, if any.
func Pipe() (r *File, w *File, err error) {
	return nil, nil, syscall.ENOSYS
}
