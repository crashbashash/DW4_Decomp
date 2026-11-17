#include "dw4/newlib/newlib_math.h"
#include <math.h>

float fmodf(float x, float y)
{
    return __ieee754_fmodf(x, y);
}
