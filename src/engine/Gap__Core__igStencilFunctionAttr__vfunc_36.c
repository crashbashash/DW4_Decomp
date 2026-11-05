/* 0x001425b0 — Gap::Core::igStencilFunctionAttr::vfunc_36: getter for the three stencil
 * operations (the `_stenFailOp`, `_stenPassZPassOp` and `_stenPassZFailOp` enum fields),
 * written through the output pointers.  Setter counterpart: vfunc_35. */
#include "dw4/reflected.h"
void Gap__Core__igStencilFunctionAttr__vfunc_36(igStencilFunctionAttr *self, int *outFailOp, int *outPassZPassOp, int *outPassZFailOp) {
    *outFailOp = self->_stenFailOp;
    *outPassZPassOp = self->_stenPassZPassOp;
    *outPassZFailOp = self->_stenPassZFailOp;
}
