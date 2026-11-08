#include "dw4/newlib_mallocr.h"

#define RONEARG struct _reent *reent_ptr
#define MALLOC_LOCK __malloc_lock(reent_ptr)
#define MALLOC_UNLOCK __malloc_unlock(reent_ptr)
void __malloc_update_mallinfo(void);
#define malloc_update_mallinfo __malloc_update_mallinfo

void __malloc_update_mallinfo(void)
{
    int i;
    mbinptr b;
    mchunkptr p;
    INTERNAL_SIZE_T avail;
    int navail;

    avail = chunksize(bin_at(0)->fd);
    navail = avail >= MINSIZE ? 1 : 0;
    for (i = 1; i < 128; ++i) {
        b = bin_at(i);
        for (p = b->bk; p != b; p = p->bk) {
            ++navail;
            avail += chunksize(p);
        }
    }
    current_mallinfo.ordblks = navail;
    current_mallinfo.uordblks = current_mallinfo.arena - avail;
    current_mallinfo.fordblks = avail;
    current_mallinfo.keepcost = chunksize(bin_at(0)->fd);
}

struct mallinfo _mallinfo_r(RONEARG)
{
  struct mallinfo ret;

  MALLOC_LOCK;
  malloc_update_mallinfo();
  ret = current_mallinfo;
  MALLOC_UNLOCK;
  return ret;
}
