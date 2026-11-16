#include "dw4/newlib_math.h"

double sqrt(double x)
{
    return __ieee754_sqrt(x);
}
