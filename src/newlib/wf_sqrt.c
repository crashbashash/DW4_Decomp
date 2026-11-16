#include "dw4/newlib_math.h"

float sqrtf(float x)
{
    return __ieee754_sqrtf(x);
}
