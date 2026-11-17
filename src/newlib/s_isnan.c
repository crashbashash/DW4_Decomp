#include "dw4/newlib/ieee_words.h"
#include <math.h>

int isnan(double x)
{
    __int32_t hx, lx;

    EXTRACT_WORDS(hx, lx, x);
    hx &= 0x7fffffff;
    hx |= (__uint32_t)(lx | -lx) >> 31;
    hx = 0x7ff00000 - hx;
    return (__uint32_t)hx >> 31;
}
