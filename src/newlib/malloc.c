#include "dw4/newlib/newlib_reent.h"
#include "dw4/newlib/newlib_mallocr.h"
#include "dw4/newlib/newlib_stdio.h"

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
