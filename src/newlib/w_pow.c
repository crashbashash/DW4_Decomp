#include "dw4/newlib/newlib_math.h"

double pow(double x, double y)
{
    return __ieee754_pow(x, y);
}
