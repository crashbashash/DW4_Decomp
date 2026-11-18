#include "dw4/newlib/newlib_reent.h"
#include "dw4/sony/libkernl.h"

char *_sbrk_r(struct _reent *ptr, int increment)
{
    char *ret;

    errno = 0;
    if ((ret = (char *)sbrk(increment)) == (char *)-1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}
