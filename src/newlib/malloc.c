#include "dw4/newlib_reent.h"

void *_malloc_r(struct _reent *ptr, unsigned int size);
void _free_r(struct _reent *ptr, void *mem);
void __malloc_lock(struct _reent *ptr);
void __malloc_unlock(struct _reent *ptr);

void *malloc(unsigned int size)
{
    void *result;

    __malloc_lock(_REENT);
    result = _malloc_r(_REENT, size);
    __malloc_unlock(_REENT);
    return result;
}

void free(void *mem)
{
    __malloc_lock(_REENT);
    _free_r(_REENT, mem);
    __malloc_unlock(_REENT);
}
