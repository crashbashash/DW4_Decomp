/* 0x0013c400 igBlendFunctionAttr vtable slot 33: field-store leaf.  Stores its argument into
 * the reflected `_dst` field (+16, igEnumMetaField in include/dw4/reflected.h), so it acts as
 * the destination-blend-factor setter (`_src` at +12 is the source factor). */
#include "dw4/reflected.h"
void Gap__Core__igBlendFunctionAttr__vfunc_33(igBlendFunctionAttr *self, int dstFactor) {
    self->_dst = dstFactor;
}
