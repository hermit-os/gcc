// Copyright 2016 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// The gccgo version of mem_*.go.

//go:build hermit

package runtime

import (
	"unsafe"
)

// Functions called by C code.
//go:linkname sysAlloc
//go:linkname sysFree

//extern hmmap
func hmmap(addr unsafe.Pointer, n uintptr, prot uint32) unsafe.Pointer

//extern hmunmap
func hmunmap(ptr unsafe.Pointer, length uintptr) int32

//extern hmprotect
func hmprotect(ptr unsafe.Pointer, length uintptr, prot uint32) int32

func init() {
}

func mmap(v unsafe.Pointer, n uintptr, prot uint32) (unsafe.Pointer, int) {
	p := hmmap(v, n, prot)
	if p == nil {
		return nil, errno()
	}
	return p, 0
}

// Don't split the stack as this method may be invoked without a valid G, which
// prevents us from allocating more stack.
//
//go:nosplit
func sysAlloc(n uintptr, sysStat *sysMemStat) unsafe.Pointer {
	p, err := mmap(nil, n, _PROT_READ|_PROT_WRITE)
	if err != 0 {
		print("runtime: mmap: access denied\n")
		exit(2)
		return nil
	}
	sysStat.add(int64(n))
	return p
}

func sysUnused(v unsafe.Pointer, n uintptr) {
}

func sysUsed(v unsafe.Pointer, n uintptr) {
	// Partially undo the NOHUGEPAGE marks from sysUnused
	// for whole huge pages between v and v+n. This may
	// leave huge pages off at the end points v and v+n
	// even though allocations may cover these entire huge
	// pages. We could detect this and undo NOHUGEPAGE on
	// the end points as well, but it's probably not worth
	// the cost because when neighboring allocations are
	// freed sysUnused will just set NOHUGEPAGE again.
	sysHugePage(v, n)
}

func sysHugePage(v unsafe.Pointer, n uintptr) {
}

// Don't split the stack as this function may be invoked without a valid G,
// which prevents us from allocating more stack.
//
//go:nosplit
func sysFree(v unsafe.Pointer, n uintptr, sysStat *sysMemStat) {
	sysStat.add(-int64(n))
	hmunmap(v, n)
}

func sysFault(v unsafe.Pointer, n uintptr) {
	mmap(v, n, _PROT_NONE)
}

func sysReserve(v unsafe.Pointer, n uintptr) unsafe.Pointer {
	p, err := mmap(v, n, _PROT_NONE)
	if err != 0 {
		return nil
	}
	return p
}

func sysMap(v unsafe.Pointer, n uintptr, sysStat *sysMemStat) {
	sysStat.add(int64(n))
	p, err := mmap(v, n, _PROT_READ|_PROT_WRITE)
	if err != 0 {
		throw("runtime: out of memory")
	}
	if p != v || err != 0 {
		throw("runtime: cannot map pages in arena address space")
	}
}
