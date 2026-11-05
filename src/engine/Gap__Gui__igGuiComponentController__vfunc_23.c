/* 0x004556b0
 * Model type check: asks whether `model` is an igGuiComponentModel (or a
 * subclass), via igObject_IsKindOf, the generic class-membership test.  The result
 * is not used here; it stays in the return register (v0). */
#include "dw4/reflected.h"
int igObject_IsKindOf();
int igGuiComponentModel_GetMetaObject();

void Gap__Gui__igGuiComponentController__vfunc_23(igGuiComponentController *self, int model) {
    igObject_IsKindOf(model, igGuiComponentModel_GetMetaObject());
}
