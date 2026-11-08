#include "dw4/newlib_stdio.h"

int fiprintf(FILE *fp, const char *fmt, ...)
{
    va_list ap;
    int ret;

    va_start(ap, fmt);
    ret = vfiprintf(fp, fmt, ap);
    va_end(ap);
    return ret;
}
