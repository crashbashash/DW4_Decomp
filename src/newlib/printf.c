#include "dw4/newlib_stdio.h"

int _printf_r(struct _reent *ptr, const char *fmt, ...)
{
    va_list ap;
    int ret;

    va_start(ap, fmt);
    ret = _vfprintf_r(ptr, ptr->_stdout, fmt, ap);
    va_end(ap);
    return ret;
}

int printf(const char *fmt, ...)
{
    va_list ap;
    int ret;

    _REENT->_stdout->_data = _REENT;
    va_start(ap, fmt);
    ret = vfprintf(_REENT->_stdout, fmt, ap);
    va_end(ap);
    return ret;
}
