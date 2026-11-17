#include "dw4/newlib/newlib_reent.h"
#include "dw4/newlib/newlib_mallocr.h"

#define M_TRIM_THRESHOLD -1
#define M_TOP_PAD -2
#define M_MMAP_THRESHOLD -3
#define M_MMAP_MAX -4

int _mallopt_r(struct _reent *ptr, int param, long value)
{
    __malloc_lock(ptr);
    switch (param) {
    case M_TRIM_THRESHOLD:
        __malloc_trim_threshold = value;
        __malloc_unlock(ptr);
        return 1;
    case M_TOP_PAD:
        __malloc_top_pad = value;
        __malloc_unlock(ptr);
        return 1;
    case M_MMAP_THRESHOLD:
        __malloc_unlock(ptr);
        return 1;
    case M_MMAP_MAX:
        __malloc_unlock(ptr);
        return value == 0;
    }
    __malloc_unlock(ptr);
    return 0;
}
