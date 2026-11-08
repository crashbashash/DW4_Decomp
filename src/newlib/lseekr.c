#include "dw4/newlib_reent.h"

extern int errno;
int lseek(int fd, int offset, int whence);

int _lseek_r(struct _reent *ptr, int fd, int offset, int whence)
{
    int ret;

    errno = 0;
    if ((ret = lseek(fd, offset, whence)) == -1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}
