#include "dw4/newlib/newlib_math.h"

double asin(double x)
{
    return __ieee754_asin(x);
}
