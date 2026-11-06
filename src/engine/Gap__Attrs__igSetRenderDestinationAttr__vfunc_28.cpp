/* Forwards to the held render-destination attribute: when `_pRDAttr` is set, call the virtual at
 * vtable byte offset 112 (slot 26) of that object, with no arguments. The call is spelled through
 * the stand-in `vX` below. */
#include "dw4/reflected.h"
extern "C" {

void Gap__Attrs__igSetRenderDestinationAttr__vfunc_28(igSetRenderDestinationAttr *self);
}
/* Stand-in receiver: the dummy virtuals only put `vX` at the right vtable slot. */
class BoundRenderDestinationVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };
void Gap__Attrs__igSetRenderDestinationAttr__vfunc_28(igSetRenderDestinationAttr *self) {
    void **renderDestination;

    renderDestination = (void **)(self->_pRDAttr);
    if (renderDestination != 0) {
        ((BoundRenderDestinationVtable *)(renderDestination))->vX();
    }
}
