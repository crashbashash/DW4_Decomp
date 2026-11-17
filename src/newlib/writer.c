#include "dw4/newlib_reent.h"
#include "dw4/libkernl.h"
#include "dw4/newlib_syscalls.h"

long _write_r(struct _reent *ptr, int fd, const void *buf, int count)
{
    long ret;

    errno = 0;
    if ((ret = (long)write(fd, buf, count)) == -1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}
