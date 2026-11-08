#include "dw4/newlib_reent.h"

extern int errno;
int kill(int pid, int sig);
int getpid(void);

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
