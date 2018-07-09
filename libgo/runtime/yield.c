// Copyright 2011 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "config.h"

#include <stddef.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sched.h>
#include <unistd.h>

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#ifdef __hermit__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif

#if defined (__i386__) || defined (__x86_64__)
#include <xmmintrin.h>
#endif

#ifdef __hermit__
void sys_usleep(unsigned long usecs);
#endif

#include "runtime.h"

/* Spin wait.  */

void
runtime_procyield (uint32 cnt)
{
  volatile uint32 i;

  for (i = 0; i < cnt; ++i)
    {
#if defined (__i386__) || defined (__x86_64__)
      _mm_pause ();
#endif
    }
}

/* Ask the OS to reschedule this thread.  */

void
runtime_osyield (void)
{
  sched_yield ();
}

/* Sleep for some number of microseconds.  */

void
runtime_usleep (uint32 us)
{
#ifdef __hermit__
  sys_usleep(us);
#else
  struct timeval tv;

  tv.tv_sec = us / 1000000;
  tv.tv_usec = us % 1000000;
  select (0, NULL, NULL, NULL, &tv);
#endif
}
