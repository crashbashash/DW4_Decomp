#include "dw4/newlib_reent.h"
#include "dw4/libkernl.h"

int _sbrk_r(struct _reent *ptr, int increment)
{
    int ret;

    errno = 0;
    if ((ret = sbrk(increment)) == -1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}
