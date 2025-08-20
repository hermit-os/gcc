/* go-mmap.c -- functions for calling C mmap functions.

   Copyright 2023 The Go Authors. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.  */

#include "config.h"

#include <stdint.h>
#include <sys/mman.h>

#ifdef __hermit__
int sys_mmap(size_t length, int prot, void** addr);
int sys_munmap(void* addr, size_t length);
int sys_mprotect(void* ptr, size_t length, int prot);

void*
hmmap(void* addr, size_t length, int prot) {
  void* p = addr;
  sys_mmap(length, prot, &p);
  return p;
}

int
hmunmap(void* addr, size_t length) {
  return sys_munmap(addr, length);
}

int
hmprotect(void* ptr, size_t length, int prot) {
  return sys_mprotect(ptr, length, prot);
}
#else
/* The exact C function to call varies between mmap and mmap64, and
   the size of the off_t argument also varies.  Here we provide a
   function that Go code can call with consistent types.  */

void *
__go_mmap(void *addr, uintptr_t length, int32_t prot, int32_t flags,
	  int32_t fd, uintptr_t offset)
{
  return mmap(addr, length, prot, flags, fd, offset);
}
#endif
