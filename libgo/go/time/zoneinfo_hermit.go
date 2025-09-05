// Copyright 2018 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build hermit

package time

var zoneSources = []string{
	"/usr/share/zoneinfo/",
	"/usr/lib/locale/TZ/",
	//runtime.GOROOT() + "/lib/time/zoneinfo.zip",
}

func initLocal() {
}