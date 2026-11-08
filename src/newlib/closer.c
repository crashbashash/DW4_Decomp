#include "dw4/newlib_reent.h"

extern int errno;
int close(int fd);

int _close_r(struct _reent *ptr, int fd)
{
    int ret;

    errno = 0;
    if ((ret = close(fd)) == -1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}
