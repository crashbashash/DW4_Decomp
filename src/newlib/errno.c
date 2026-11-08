#include "dw4/newlib_reent.h"

int *__errno(void)
{
    return &_REENT->_errno;
}
