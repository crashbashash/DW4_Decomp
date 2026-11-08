#include "dw4/ieee_words.h"

extern double __ieee754_log(double);
static const double two54 = 1.80143985094819840000e+16,
                    ivln10 = 4.34294481903251816668e-01,
                    log10_2hi = 3.01029995663611771306e-01,
                    log10_2lo = 3.69423907715893078616e-13;
static const double zero = 0.0;

double __ieee754_log10(double x)
{
    double y, z;
    int i, k, hx;
    unsigned lx;

    EXTRACT_WORDS(hx, lx, x);

    k = 0;
    if (hx < 0x00100000) {
        if (((hx & 0x7fffffff) | lx) == 0)
            return -two54 / zero;
        if (hx < 0)
            return (x - x) / zero;
        k -= 54;
        x *= two54;
        GET_HIGH_WORD(hx, x);
    }
    if (hx >= 0x7ff00000)
        return x + x;
    k += (hx >> 20) - 1023;
    i = ((unsigned)k & 0x80000000) >> 31;
    hx = (hx & 0x000fffff) | ((0x3ff - i) << 20);
    y = (double)(k + i);
    SET_HIGH_WORD(x, hx);
    z = y * log10_2lo + ivln10 * __ieee754_log(x);
    return z + y * log10_2hi;
}
