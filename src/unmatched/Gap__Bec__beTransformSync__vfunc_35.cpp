#include "dw4/reflected.h"
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
class TransformSyncChildVirtualSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();  virtual int vX(int); };
extern "C" {
int Matrix44_Copy(...);
void Gap__Bec__beTransformSync__vfunc_35(beTransformSync *arg0, int arg1);
}
void Gap__Bec__beTransformSync__vfunc_35(beTransformSync *arg0, int arg1) {
    int temp_s2; int var_s1; int var_s0;

    Matrix44_Copy((char *)arg0 + 0x20, arg1);
    temp_s2 = ((igObjectList *)arg0->_syncTransformList)->_count;
    var_s1 = 0;
    if (0 < temp_s2) {
        var_s0 = 0;
        do {
            TransformSyncChildVirtualSlots *o = *(TransformSyncChildVirtualSlots **)((char *)((igObjectList *)arg0->_syncTransformList)->_data + var_s0);
            o->vX(arg1);
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < temp_s2);
    }
}
