// Copyright 2012 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// +build linux dragonfly openbsd solaris

package tar

import (
	"syscall"
	"time"
)

func statAtime(st *syscall.Stat_t) time.Time {
	return time.Unix(0,0) //st.Atim.Unix())
}

func statCtime(st *syscall.Stat_t) time.Time {
	return time.Unix(0,0) //st.Ctim.Unix())
}
