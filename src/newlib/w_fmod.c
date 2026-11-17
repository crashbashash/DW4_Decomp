#include "dw4/newlib/newlib_math.h"

double fmod(double x, double y)
{
    return __ieee754_fmod(x, y);
}
