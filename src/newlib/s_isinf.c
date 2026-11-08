#include "dw4/ieee_words.h"

int isinf(double x)
{
    __int32_t hx, lx;

    EXTRACT_WORDS(hx, lx, x);
    hx &= 0x7fffffff;
    hx |= (__uint32_t)(lx | -lx) >> 31;
    hx = 0x7ff00000 - hx;
    return 1 - (int)((__uint32_t)(hx | -hx) >> 31);
}
