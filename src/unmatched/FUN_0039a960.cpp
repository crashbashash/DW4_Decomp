#include "dw4/reflected.h"
extern "C" {
long long __fixsfdi(float);
void FUN_0039a960(beNodeAnim *arg0, long long arg1, long long arg2);
}
void FUN_0039a960(beNodeAnim *arg0, long long arg1, long long arg2) {
    long long r;
    float f;
    f = (float)(unsigned int)(int)(arg2 >> 0x12);
    f = f * arg0->_timeScale;
    r = __fixsfdi(f);
    arg0->_timeBias = arg1 - (r << 0x12);
}
