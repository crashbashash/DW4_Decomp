#include "dw4/newlib_reent.h"
#include "dw4/newlib_mallocr.h"

void *_realloc_r(struct _reent *ptr, void *mem, unsigned int size);

void *realloc(void *mem, unsigned int size)
{
    void *result;

    __malloc_lock(_REENT);
    result = _realloc_r(_REENT, mem, size);
    __malloc_unlock(_REENT);
    return result;
}
