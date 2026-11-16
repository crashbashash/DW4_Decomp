#include "dw4/newlib_math.h"

float logf(float x)
{
    return __ieee754_logf(x);
}
