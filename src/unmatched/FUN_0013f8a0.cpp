#include "dw4/reflected.h"
extern "C" {
int __moddi3(long long, int);
int __divdi3(long long, int);
float __floatdisf(int);
}
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int, int, int *, float); };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void vX(); };
extern "C" void FUN_0013f8a0(igParticleAttr *arg0, char *arg1) {
    int sp4C;
    float temp_f20;
    float t2;
    long long temp_s1;
    if (arg0->_bUseCurrentTime != 0) {
        if (arg0->_startTime == -1) {
            arg0->_startTime = *(long long *)(arg1 + 96);
        }
        temp_s1 = *(long long *)(arg1 + 96) - arg0->_startTime;
        temp_f20 = __floatdisf(__moddi3(temp_s1, 1000000000)) / (float)1000000000;
        t2 = __floatdisf(__divdi3(temp_s1, 1000000000));
        arg0->_time = t2 + temp_f20;
    }
    ((A *)arg0->_particleArray)->vX(arg0->_particleNum, arg0->_particleOffset, &sp4C, arg0->_time + arg0->_offset);
    if (sp4C == 0) {
        ((B *)arg0->_particleArray)->vX();
    }
}
