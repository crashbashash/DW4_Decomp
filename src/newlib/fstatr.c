#include "dw4/newlib/newlib_reent.h"
#include "dw4/sony/libkernl.h"
#include "dw4/newlib/newlib_syscalls.h"

int _fstat_r(struct _reent *ptr, int fd, struct stat *st)
{
    int ret;

    errno = 0;
    if ((ret = fstat(fd, st)) == -1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}
