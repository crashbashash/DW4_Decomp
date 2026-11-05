#include "dw4/reflected.h"
extern "C" {
int FUN_00166d40(...);
void Gap__Bec__ParticleArray__vfunc_15(void *arg0);
}
/* matching construct: dummy-virtual receiver; vX is the retail vtable call at slot 21 */
class DW4VC_92_5 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int, int, int, float, float); };
void Gap__Bec__ParticleArray__vfunc_15(void *arg0) {
    int temp_v0;

    temp_v0 = FUN_00166d40();
    if (temp_v0 != 0) {
        ((DW4VC_92_5 *)(((char *)(arg0) + 0)))->vX((int)(((ParticleArray *)arg0)->_particleFormat), (int)(*(int *)((char *)(arg0) + 12)), (int)(temp_v0), ((ParticleArray *)arg0)->_particleLifeStart, ((ParticleArray *)arg0)->_particleLifeEnd);
    }
}
