#include "dw4/newlib/newlib_math.h"

double log(double x)
{
    return __ieee754_log(x);
}
