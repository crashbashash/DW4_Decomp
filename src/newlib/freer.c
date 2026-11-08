#include "dw4/newlib_mallocr.h"

#define RARG struct _reent *reent_ptr,
#define MALLOC_LOCK __malloc_lock(reent_ptr)
#define MALLOC_UNLOCK __malloc_unlock(reent_ptr)
#define malloc_getpagesize 4096
#define check_chunk(P)

void _free_r(struct _reent *reent_ptr, void *mem)
{
    mchunkptr p;
    INTERNAL_SIZE_T hd;
    INTERNAL_SIZE_T sz;
    int idx;
    mchunkptr next;
    INTERNAL_SIZE_T nextsz;
    INTERNAL_SIZE_T prevsz;
    mchunkptr bck;
    mchunkptr fwd;
    int islr;

    if (mem == 0)
        return;
    __malloc_lock(reent_ptr);
    p = mem2chunk(mem);
    hd = p->size;
    sz = hd & ~PREV_INUSE;
    next = chunk_at_offset(p, sz);
    nextsz = chunksize(next);
    if (next == top) {
        sz += nextsz;
        if (!(hd & PREV_INUSE)) {
            prevsz = p->prev_size;
            p = chunk_at_offset(p, -prevsz);
            sz += prevsz;
            unlink(p, bck, fwd);
        }
        set_head(p, sz | PREV_INUSE);
        top = p;
        if ((unsigned long)(sz) >= (unsigned long)trim_threshold)
            _malloc_trim_r(reent_ptr, top_pad);
        __malloc_unlock(reent_ptr);
        return;
    }
    set_head(next, nextsz);
    islr = 0;
    if (!(hd & PREV_INUSE)) {
        prevsz = p->prev_size;
        p = chunk_at_offset(p, -prevsz);
        sz += prevsz;
        if (p->fd == last_remainder)
            islr = 1;
        else
            unlink(p, bck, fwd);
    }
    if (!(inuse_bit_at_offset(next, nextsz))) {
        sz += nextsz;
        if (!islr && next->fd == last_remainder) {
            islr = 1;
            link_last_remainder(p);
        } else
            unlink(next, bck, fwd);
    }
    set_head(p, sz | PREV_INUSE);
    set_foot(p, sz);
    if (!islr)
        frontlink(p, sz, idx, bck, fwd);
    __malloc_unlock(reent_ptr);
}

int _malloc_trim_r(RARG size_t pad)
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
