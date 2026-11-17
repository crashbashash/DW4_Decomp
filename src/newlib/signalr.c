#include "dw4/newlib_reent.h"
#include "dw4/libkernl.h"
#include "dw4/newlib_syscalls.h"

int _kill_r(struct _reent *ptr, int pid, int sig)
{
    int ret;

    errno = 0;
    if ((ret = kill(pid, sig)) == -1 && errno != 0) {
        ptr->_errno = errno;
    }
    return ret;
}

int _getpid_r(struct _reent *ptr)
{
    return getpid();
}
