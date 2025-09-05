// Copyright 2020 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build hermit
// +build hermit

// Hermit OS library calls.

package syscall

func ReadDirent(fd int, buf []byte) (n int, err error) {
	return 0, ENOSYS
}


func Accept4(fd int, flags int) (nfd int, sa Sockaddr, err error) {
	return -1, nil, ENOSYS
}