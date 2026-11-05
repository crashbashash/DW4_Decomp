/* 0x0013f000
 * Forwards to the held light: when `_light` is set, call the virtual at vtable
 * byte offset 116 (slot 27) of that object, with no arguments.
 * Evidence: the function's machine code is lw a0,16(a0); null guard; lw t9,116(t9);
 * jalr, and +16 is igLightStateAttr::_light (include/dw4/reflected.h).  What the
 * slot does is not established, so the call is spelled through the stand-in
 * `vX` below. */
#include "dw4/reflected.h"
extern "C" {

void Gap__Core__igLightStateAttr__vfunc_29(igLightStateAttr *self);
}
/* Stand-in receiver: the dummy virtuals only put `vX` at the right vtable slot. */
class BoundLightVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(); };
void Gap__Core__igLightStateAttr__vfunc_29(igLightStateAttr *self) {
    void **light;

    light = (void **)(self->_light);
    if (light != 0) {
        ((BoundLightVtable *)(light))->vX();
    }
}
