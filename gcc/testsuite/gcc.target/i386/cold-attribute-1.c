/* { dg-do compile } */
/* { dg-options "-O2" } */
#include <string.h>
static inline
__attribute__ ((cold))
my_cold_memset (void *a, int b,int c)
{
  memset (a,b,c);
}
t(void *a,int b,int c)
{
  if (a)
    my_cold_memset (a,b,c);
}

/* The IF conditional should be predicted as cold and my_cold_memset inlined
   for size expanding memset as rep; stosb.  */
/* { dg-final { scan-assembler "stosb" } } */
