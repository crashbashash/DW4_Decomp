#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(...);
int Memory_FreeBuffer(...);
int igMetaObject_CountInstances(...);
void Gap__Bec__beSvPs2McImage128k__vfunc_08(void *arg0);
}
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
class SvPs2McImageVirtualSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void Gap__Bec__beSvPs2McImage128k__vfunc_08(void *arg0) {
    beSvPs2McImage128k *o = (beSvPs2McImage128k *)arg0;
    if (o->_data != 0) {
        Memory_FreeBuffer(o->_data);
    }
    o->_data = 0;
    igMetaObject_CountInstances(((SvPs2McImageVirtualSlots *)(((char *)(arg0) + 0)))->vX(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
