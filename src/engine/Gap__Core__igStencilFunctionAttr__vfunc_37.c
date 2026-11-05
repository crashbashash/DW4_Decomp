/* 0x001425d0 igStencilFunctionAttr vtable slot 37: setter for the reflected _readMask field
 * (the stencil compare mask; field offsets from include/dw4/reflected.h). */
#include "dw4/reflected.h"
void Gap__Core__igStencilFunctionAttr__vfunc_37(igStencilFunctionAttr *self, int read_mask) {
    self->_readMask = read_mask;
}
