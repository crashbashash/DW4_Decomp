#include "dw4/newlib_stdio.h"

int vprintf(const char *fmt, va_list ap)
{
    return vfprintf(_REENT->_stdout, fmt, ap);
}
