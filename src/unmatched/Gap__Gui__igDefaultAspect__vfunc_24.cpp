#include "dw4/reflected.h"
extern "C" {

void Gap__Gui__igDefaultAspect__vfunc_24(igDefaultAspect *arg0, int *arg1);
}
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
class DW4VC_104_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
class DW4VC_108_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int); };
void Gap__Gui__igDefaultAspect__vfunc_24(igDefaultAspect *arg0, int *arg1) {
    int temp_a2;

    temp_a2 = *arg1;
    switch (temp_a2) {
    case 0:
        ((DW4VC_100_1 *)(((char *)(arg0) + 0)))->vX((int)(arg1));
        return;
    case 1:
        ((DW4VC_104_1 *)(((char *)(arg0) + 0)))->vX((int)(arg1));
        return;
    default:
        if (arg0->_model != 0) {
            ((DW4VC_108_1 *)(((char *)(arg0) + 0)))->vX((int)(arg1));
        }
        return;
    }
}
