// Copyright 2019 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build !hermit
// +build !hermit

package syscall

//sys	FcntlFlock(fd uintptr, cmd int, lk *Flock_t) (err error)
//__go_fcntl_flock(fd _C_int, cmd _C_int, arg *Flock_t) _C_int
