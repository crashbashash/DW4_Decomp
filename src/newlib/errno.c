#include "dw4/newlib/newlib_reent.h"

int *__errno(void)
{
    return &_REENT->_errno;
}
