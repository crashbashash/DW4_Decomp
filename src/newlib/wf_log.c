#include "dw4/newlib/newlib_math.h"

float logf(float x)
{
    return __ieee754_logf(x);
}
