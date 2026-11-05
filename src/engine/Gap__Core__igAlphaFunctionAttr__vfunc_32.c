/* 0x0013b780 igAlphaFunctionAttr vtable slot 32: field-store leaf.  Stores its argument into
 * the reflected `_func` field (+12, igEnumMetaField in include/dw4/reflected.h), so it acts as
 * the alpha-test comparison-function setter (`_refValue` at +16 is the reference it compares to). */
#include "dw4/reflected.h"
void Gap__Core__igAlphaFunctionAttr__vfunc_32(igAlphaFunctionAttr *self, int func) {
    self->_func = func;
}
