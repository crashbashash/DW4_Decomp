#include "dw4/reflected.h"
extern "C" {
int Memory_AllocateDefaultBuffer(...);
int Gap__Core__igObject__vfunc_07(...);
int igMetaObject_CountInstances(...);
void Gap__Bec__beXboxImage24k__vfunc_07(beXboxImage24k *arg0, int arg1);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void Gap__Bec__beXboxImage24k__vfunc_07(beXboxImage24k *arg0, int arg1) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX(), 1);
    if (!(arg1 & 0xFF)) {
        arg0->_data = Memory_AllocateDefaultBuffer(0x6000);
        arg0->_dataSize = 0x6000;
    }
}
