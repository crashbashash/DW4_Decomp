#include "dw4/newlib_math.h"

float atan2f(float y, float x)
{
    return __ieee754_atan2f(y, x);
}
