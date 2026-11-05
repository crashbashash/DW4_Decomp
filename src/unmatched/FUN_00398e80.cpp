#include "dw4/reflected.h"
extern "C" {
long long FUN_00230110(float);
long long FUN_00398e80(beModelCtrlNode2 *arg0, long long arg1);
}

long long FUN_00398e80(beModelCtrlNode2 *arg0, long long arg1) {
    unsigned int u = (unsigned int)(arg1 >> 0x12);
    float f = (float)u;
    long long r;
    f = f * arg0->_timeScale;
    r = FUN_00230110(f) << 0x12;
    return r + arg0->_timeBias;
}
