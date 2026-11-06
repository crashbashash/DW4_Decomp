/* Model type check: asks whether `model` is an igGuiComponentModel (or a subclass), via
 * igObject_IsKindOf, the generic class-membership test. The result is not used here; it stays in
 * the return register (v0). Same body as igGuiComponentController::vfunc_23 (slot 23 of both
 * vtables). */
#include "dw4/reflected.h"
int igObject_IsKindOf();
int igGuiComponentModel_GetMetaObject();

void Gap__Gui__igDefaultAspect__vfunc_23(igDefaultAspect *self, int model) {
    igObject_IsKindOf(model, igGuiComponentModel_GetMetaObject());
}
