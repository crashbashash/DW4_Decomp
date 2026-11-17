#include "dw4/newlib_syscalls.h"
#include <signal.h>

void abort(void)
{
    for (;;) {
        raise(6);
        _exit(1);
    }
}
