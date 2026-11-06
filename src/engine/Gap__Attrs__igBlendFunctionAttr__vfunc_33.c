/* Setter for the destination blend factor (`_dst`, +16); `_src` at +12 is the source factor. */
#include "dw4/reflected.h"
void Gap__Attrs__igBlendFunctionAttr__vfunc_33(igBlendFunctionAttr *self, int dstFactor) {
    self->_dst = dstFactor;
}
