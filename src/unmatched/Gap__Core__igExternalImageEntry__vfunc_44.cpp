#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(igObject *);
int igObject_GetAllocator();
igObject *FUN_0014df70(int);
int FUN_001551f0(void *, igObject *);
}
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable slot */
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(igObject *); };
extern "C" int Gap__Core__igExternalImageEntry__vfunc_44(A *arg0) {
    igObject *temp_v0;
    temp_v0 = FUN_0014df70(igObject_GetAllocator());
    if (FUN_001551f0(arg0, temp_v0) == 0) {
        temp_v0->_refCount = temp_v0->_refCount - 1;
        if ((temp_v0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_v0);
        }
        return 0;
    }
    arg0->vX(temp_v0);
    temp_v0->_refCount = temp_v0->_refCount - 1;
    if ((temp_v0->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(temp_v0);
    }
    return 1;
}
