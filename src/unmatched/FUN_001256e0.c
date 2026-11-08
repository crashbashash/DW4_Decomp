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
int FUN_001256e0(RARG size_t pad)
{
  long  top_size;        /* Amount of top-most memory */
  long  extra;           /* Amount to release */
  char* current_brk;     /* address returned by pre-check sbrk call */
  char* new_brk;         /* address returned by negative sbrk call */

  unsigned long pagesz = malloc_getpagesize;

  MALLOC_LOCK;

  top_size = chunksize(top);
  extra = ((top_size - pad - MINSIZE + (pagesz-1)) / pagesz - 1) * pagesz;

  if (extra < (long)pagesz)  /* Not enough memory to release */
  {
    MALLOC_UNLOCK;
    return 0;
  }

  else
  {
    /* Test to make sure no one else called sbrk */
    current_brk = (char*)(MORECORE (0));
    if (current_brk != (char*)(top) + top_size)
    {
      MALLOC_UNLOCK;
      return 0;     /* Apparently we don't own memory; must fail */
    }

    else
    {
      new_brk = (char*)(MORECORE (-extra));
      
      if (new_brk == (char*)(MORECORE_FAILURE)) /* sbrk failed? */
      {
        /* Try to figure out what we have */
        current_brk = (char*)(MORECORE (0));
        top_size = current_brk - (char*)top;
        if (top_size >= (long)MINSIZE) /* if not, we are very very dead! */
        {
          sbrked_mem = current_brk - sbrk_base;
          set_head(top, top_size | PREV_INUSE);
        }
        check_chunk(top);
	MALLOC_UNLOCK;
        return 0; 
      }

      else
      {
        /* Success. Adjust top accordingly. */
        set_head(top, (top_size - extra) | PREV_INUSE);
        sbrked_mem -= extra;
        check_chunk(top);
	MALLOC_UNLOCK;
        return 1;
      }
    }
  }
}

