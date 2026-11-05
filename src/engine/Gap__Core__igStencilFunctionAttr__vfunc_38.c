/* 0x001425e0 — Gap::Core::igStencilFunctionAttr::vfunc_38: setter for the `_writeMask` field.
 * vfunc_37 sets `_readMask`, vfunc_32 `_refVal`. */
#include "dw4/reflected.h"
void Gap__Core__igStencilFunctionAttr__vfunc_38(igStencilFunctionAttr *self, int writeMask) {
    self->_writeMask = writeMask;
}
