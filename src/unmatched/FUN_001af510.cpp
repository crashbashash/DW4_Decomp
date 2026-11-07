#include "dw4/reflected.h"
extern long long DAT_0048d8c0;
extern float DAT_0048d8c8;
extern long long DAT_00562570;
extern "C" {
long long FUN_00230110(float x);
void FUN_001af510(igAnimationState *s, long long t);
}
void FUN_001af510(igAnimationState *s, long long t) {
    long long r; float x;
    if (DAT_0048d8c0 != t || DAT_0048d8c8 != s->_timeScale) {
        x = (float)(unsigned int)(int)(t >> 18);
        x *= s->_timeScale;
        DAT_00562570 = FUN_00230110(x);
        DAT_0048d8c0 = t;
        DAT_0048d8c8 = s->_timeScale;
    }
    r = DAT_00562570 << 18;
    r += s->_timeBias;
    s->_localTime = r;
}
