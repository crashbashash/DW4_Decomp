#include "dw4/newlib_math.h"

double atan2(double y, double x)
{
    return __ieee754_atan2(y, x);
}
