/* Configuration for GNU C-compiler for PowerPC running System V.4.
   Copyright (C) 1995, 1998, 1999, 2001 Free Software Foundation, Inc.
   Cloned from sparc/xm-sysv4.h by Michael Meissner (meissner@cygnus.com).

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* This describes the machine the compiler is hosted on.  */
/* Doubles are stored in memory with the high order word first.  This
   matters when cross-compiling.  */
#define HOST_WORDS_BIG_ENDIAN 1

/* if not compiled with GNU C, use only int bitfields. */
#ifndef __GNUC__
#undef ONLY_INT_FIELDS
#define ONLY_INT_FIELDS
#endif
