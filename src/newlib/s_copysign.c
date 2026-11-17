#include "dw4/newlib/ieee_words.h"
#include <math.h>

double copysign(double x, double y)
{
    __uint32_t hx, hy;

    GET_HIGH_WORD(hx, x);
    GET_HIGH_WORD(hy, y);
    SET_HIGH_WORD(x, (hx & 0x7fffffff) | (hy & 0x80000000));
    return x;
}
