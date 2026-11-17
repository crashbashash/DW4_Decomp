#include "dw4/newlib_reent.h"
#include "dw4/libkernl.h"

long _read_r(struct _reent *ptr, int fd, void *buf, int count)
{
    long ret;

    errno = 0;
    if ((ret = (long)read(fd, buf, count)) == -1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}
