#include "dw4/newlib_reent.h"
#include "dw4/newlib_mallocr.h"

void *_calloc_r(struct _reent *ptr, unsigned int n, unsigned int size);

void *calloc(unsigned int n, unsigned int size)
{
    void *result;

    __malloc_lock(_REENT);
    result = _calloc_r(_REENT, n, size);
    __malloc_unlock(_REENT);
    return result;
}
