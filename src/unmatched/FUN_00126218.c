/* newlib mallocr.c pieces. */
#include "dw4/newlib_mallocr.h"

typedef unsigned int size_t;
#define RARG Reent *reent_ptr,
#define RONEARG Reent *reent_ptr
#define RCALL reent_ptr,
#define RONECALL reent_ptr
#define MALLOC_LOCK FUN_00127310(reent_ptr)
#define MALLOC_UNLOCK FUN_00127390(reent_ptr)
#define malloc_getpagesize 4096
#define check_chunk(P)
#define check_malloc_state()
#define check_inuse_chunk(P)
#define check_free_chunk(P)
#define check_malloced_chunk(P, N)
#define Void_t void
void FUN_00126180(void);
#define malloc_update_mallinfo FUN_00126180
struct mallinfo FUN_00126218(RONEARG)
{
  struct mallinfo ret;

  MALLOC_LOCK;
  malloc_update_mallinfo();
  ret = current_mallinfo;
  MALLOC_UNLOCK;
  return ret;
}
