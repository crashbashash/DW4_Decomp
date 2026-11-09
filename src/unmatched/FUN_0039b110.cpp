extern "C" {
float atan2f(float, float);
float sqrtf(float);
}
#include "dw4/reflected.h"
extern "C" {
void FUN_0039b110(bePadData *arg0, int *arg1, float *arg2);
}
void FUN_0039b110(bePadData *arg0, int *arg1, float *arg2) {
    const float *view = arg2;
    float d;
    float ang;
    float half;
    float y, x;
    x = view[0];
    y = view[1];
    d = sqrtf(x * x + y * y);
    ang = atan2f(arg2[1], arg2[0]);
    half = 0.5f * arg0->_adAngle;
    *arg1 = 0;
    if (!(d < arg0->_enaLen)) {
        if (ang < -2.3561945f + half) {
            *arg1 |= 8;
        }
        if (!(ang < -2.3561945f - half) && (ang <= -0.7853982f + half)) {
            *arg1 |= 4;
        }
        if (!(ang <= -0.7853982f - half) && (ang < 0.7853982f + half)) {
            *arg1 |= 2;
        }
        if (!(ang < 0.7853982f - half) && (ang <= 2.3561945f + half)) {
            *arg1 |= 1;
        }
        if (!(ang <= 2.3561945f - half)) {
            *arg1 |= 8;
        }
    }
}
