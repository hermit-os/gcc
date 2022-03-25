#include <stdio.h>
#include <errno.h>

#include "runtime.h"
#include "arch.h"
#include "malloc.h"

#define PAGE_FLOOR(addr)	(((addr) + PageSize - 1) & ~(PageSize-1))

void*
runtime_SysAlloc(uintptr n, uint64 *stat)
{
	USED(stat);
	void *p;

#ifdef __hermit__
	size_t addr = (size_t) malloc(n+PageSize+sizeof(size_t));
	if (!addr)
		return NULL;

	if ((addr % PageSize) == 0) {
		p = (void*) (addr + PageSize);
	} else {
		// this works because newlib smallest chunk size is 32 byte
		// => enough space for a size_t (8 byte)
		p = (void*) PAGE_FLOOR(addr);
	}
	*((size_t*) p - 1) = addr;
#else
	errno = posix_memalign(&p, PageSize, n);
	if (errno > 0) {
		perror("posix_memalign");
		exit(2);
	}
#endif
	if (stat)
		runtime_xadd64(stat, n);

	return p;
}

void
runtime_SysUsed(void *v, uintptr n)
{
	USED(v);
	USED(n);
}

void
runtime_SysUnused(void *v, uintptr n)
{
	USED(v);
	USED(n);
	// TODO(rsc): call madvise MADV_DONTNEED
}

void
runtime_SysFree(void *v, uintptr n, uint64 *stat)
{
	USED(stat);

#ifdef __hermit__
	size_t addr = *((size_t*) v - 1);
	free((void*) addr);
#else
	free(v);
#endif

	if (stat)
		runtime_xadd64(stat, -(uint64)n);
}

// add dummy pointer for "runtime/malloc.goc"
char* _end = NULL;

void*
runtime_SysReserve(void *v, uintptr n, bool* reserved)
{
	USED(v);
	USED(reserved);
	return runtime_SysAlloc(n, NULL);
}

void
runtime_SysMap(void *v, uintptr n, bool reserved, uint64 *stat)
{
	USED(v);
	USED(n);
	USED(stat);
	USED(reserved);
}

void
runtime_SysFault(void *v, uintptr n)
{
	USED(v);
	USED(n);
}
