/* Setter for the three stencil operations (the `_stenFailOp`, `_stenPassZPassOp` and
 * `_stenPassZFailOp` enum fields). Getter counterpart: vfunc_36. */
#include "dw4/reflected.h"
void Gap__Core__igStencilFunctionAttr__vfunc_35(igStencilFunctionAttr *self, int failOp, int passZPassOp, int passZFailOp) {
    self->_stenFailOp = failOp;
    self->_stenPassZPassOp = passZPassOp;
    self->_stenPassZFailOp = passZFailOp;
}
