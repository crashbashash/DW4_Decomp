#include "dw4/newlib_reent.h"
#include "dw4/libkernl.h"
#include "dw4/newlib_syscalls.h"

int _close_r(struct _reent *ptr, int fd)
{
    int ret;

    errno = 0;
    if ((ret = close(fd)) == -1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}
