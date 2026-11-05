#include "dw4/reflected.h"
extern "C" {
long long FUN_00230110(float);
void FUN_0039a960(beNodeAnim *arg0, long long arg1, long long arg2);
}
void FUN_0039a960(beNodeAnim *arg0, long long arg1, long long arg2) {
    long long r;
    float f;
    f = (float)(unsigned int)(int)(arg2 >> 0x12);
    f = f * arg0->_timeScale;
    r = FUN_00230110(f);
    arg0->_timeBias = arg1 - (r << 0x12);
}
