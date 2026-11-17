#include "dw4/newlib_reent.h"
#include "dw4/libkernl.h"

int _fstat_r(struct _reent *ptr, int fd, void *st)
{
    int ret;

    errno = 0;
    if ((ret = fstat(fd, st)) == -1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}
