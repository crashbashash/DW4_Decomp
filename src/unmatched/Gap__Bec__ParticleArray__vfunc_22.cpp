#include "dw4/reflected.h"
extern "C" {
int Gap__Bec__ParticleArray__vfunc_22(ParticleArray *arg0, int arg1);
}
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int, int); };
int Gap__Bec__ParticleArray__vfunc_22(ParticleArray *arg0, int arg1) {
    ((DW4VC_100_1 *)arg0)->vX(arg1, arg0->_arrayIndex);
    return arg0->_arrayIndex - 1;
}
