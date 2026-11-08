#include "dw4/newlib_stdio.h"

unsigned int strlen(const char *s);
int eofread(void *cookie, char *buf, int len);

int eofread(void *cookie, char *buf, int len)
{
    return 0;
}

int sscanf(const char *str, const char *fmt, ...)
{
    int ret;
    va_list ap;
    FILE f;

    f._flags = __SRD;
    f._bf._base = f._p = (unsigned char *)str;
    f._bf._size = f._r = strlen(str);
    f._read = eofread;
    f._ub._base = 0;
    f._lb._base = 0;
    f._data = _REENT;
    va_start(ap, fmt);
    ret = __svfscanf(&f, fmt, ap);
    va_end(ap);
    return ret;
}
