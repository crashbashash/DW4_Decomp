#include "dw4/ieee_words.h"

int finite(double x)
{
    __int32_t hx;

    GET_HIGH_WORD(hx, x);
    return (int)((__uint32_t)((hx & 0x7fffffff) - 0x7ff00000) >> 31);
}
