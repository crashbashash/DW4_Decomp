#include "dw4/newlib_reent.h"

extern int errno;
int sbrk(int increment);

int _sbrk_r(struct _reent *ptr, int increment)
{
    int ret;

    errno = 0;
    if ((ret = sbrk(increment)) == -1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}
