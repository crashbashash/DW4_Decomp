#include "dw4/newlib_stdio.h"

#define INT_MAX 0x7fffffff

int _snprintf_r(struct _reent *ptr, char *str, unsigned int size, const char *fmt, ...)
{
    int ret;
    va_list ap;
    FILE f;

    f._flags = __SWR | __SSTR;
    f._bf._base = f._p = (unsigned char *)str;
    f._bf._size = f._w = (size > 0 ? size - 1 : 0);
    f._data = ptr;
    va_start(ap, fmt);
    ret = vfprintf(&f, fmt, ap);
    va_end(ap);
    if (size > 0) {
        *f._p = 0;
    }
    return ret;
}

int snprintf(char *str, unsigned int size, const char *fmt, ...)
{
    int ret;
    va_list ap;
    FILE f;

    f._flags = __SWR | __SSTR;
    f._bf._base = f._p = (unsigned char *)str;
    f._bf._size = f._w = (size > 0 ? size - 1 : 0);
    f._data = _REENT;
    va_start(ap, fmt);
    ret = vfprintf(&f, fmt, ap);
    va_end(ap);
    if (size > 0) {
        *f._p = 0;
    }
    return ret;
}
