#include "dw4/newlib_math.h"

double exp(double x)
{
    return __ieee754_exp(x);
}
