#include "dw4/newlib_reent.h"

void *_realloc_r(struct _reent *ptr, void *mem, unsigned int size);
void __malloc_lock(struct _reent *ptr);
void __malloc_unlock(struct _reent *ptr);

void *realloc(void *mem, unsigned int size)
{
    void *result;

    __malloc_lock(_REENT);
    result = _realloc_r(_REENT, mem, size);
    __malloc_unlock(_REENT);
    return result;
}
