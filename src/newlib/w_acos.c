#include "dw4/newlib/newlib_math.h"

double acos(double x)
{
    return __ieee754_acos(x);
}
