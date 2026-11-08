#include "dw4/newlib_reent.h"

void *_calloc_r(struct _reent *ptr, unsigned int n, unsigned int size);
void __malloc_lock(struct _reent *ptr);
void __malloc_unlock(struct _reent *ptr);

void *calloc(unsigned int n, unsigned int size)
{
    void *result;

    __malloc_lock(_REENT);
    result = _calloc_r(_REENT, n, size);
    __malloc_unlock(_REENT);
    return result;
}
