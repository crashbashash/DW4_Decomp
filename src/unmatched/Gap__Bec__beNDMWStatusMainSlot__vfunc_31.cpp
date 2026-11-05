/* 0x00416550 - Gap__Bec__beNDMWStatusMainSlot__vfunc_31. class with data members, forwarded receiver argument; alternate compiler -O3,p (pads the join target) Verified byte-identical by tools/verify.py. */
#include "dw4/reflected.h"
/* matching construct: dummy-virtual class (38 slots) so arg0->vX() compiles to the retail vtable call; data is read through the reflected view below. */
class beNDMWStatusMainSlotVTable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void vX(); };
extern "C" {
int beNDMWStatus_AssignEquipment(void *, int, int, int);
void Gap__Bec__beNDMWStatusMainSlot__vfunc_31(beNDMWStatusMainSlotVTable *arg0);
}
void Gap__Bec__beNDMWStatusMainSlot__vfunc_31(beNDMWStatusMainSlotVTable *arg0) {
    beNDMWStatusMainSlot *s = (beNDMWStatusMainSlot *)arg0;
    beNDMWStatus_AssignEquipment(arg0, s->_mainSlot, s->_kindListPos, s->_retCode);
    if (s->_kindListPos == 0) {
        arg0->vX();
    }
}
