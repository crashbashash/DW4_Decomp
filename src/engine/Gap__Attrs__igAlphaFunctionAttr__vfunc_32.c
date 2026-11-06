/* Setter for the alpha-test comparison function (`_func`, +12); `_refValue` at +16 is the
 * reference it compares to. */
#include "dw4/reflected.h"
void Gap__Attrs__igAlphaFunctionAttr__vfunc_32(igAlphaFunctionAttr *self, int func) {
    self->_func = func;
}
