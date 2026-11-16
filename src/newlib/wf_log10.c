#include "dw4/newlib_math.h"

float log10f(float x)
{
    return __ieee754_log10f(x);
}
