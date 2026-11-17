#include "dw4/newlib/newlib_math.h"

double log10(double x)
{
    return __ieee754_log10(x);
}
