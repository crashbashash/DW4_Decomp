#include "dw4/reflected.h"
/* 0x0036fe80 - Gap__Bec__beSvPlatDataGC__vfunc_08. class with data members after the vtable; alternate compiler -O3,p (nop fill) Verified byte-identical by tools/verify.py. */
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
class SvPlatDataGCVirtualSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *vX(); };
extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(...);
int Memory_FreeBuffer(...);
int igMetaObject_CountInstances(...);
void Gap__Bec__beSvPlatDataGC__vfunc_08(beSvPlatDataGC *arg0);
}
void Gap__Bec__beSvPlatDataGC__vfunc_08(beSvPlatDataGC *arg0) {
    if (arg0->_banTplData != 0) {
        Memory_FreeBuffer(arg0->_banTplData);
    }
    if (arg0->_iconTplData != 0) {
        Memory_FreeBuffer(arg0->_iconTplData);
    }
    arg0->_banTplData = 0;
    arg0->_iconTplData = 0;
    igMetaObject_CountInstances(((SvPlatDataGCVirtualSlots *)arg0)->vX(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
