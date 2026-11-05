/* 0x0013cae0 igCullFaceAttr vtable slot 32: field-store leaf.  Stores its argument into the
 * reflected `_mode` field (+16, igEnumMetaField in include/dw4/reflected.h), so it acts as
 * the cull-mode setter (slot 33 is the matching `_enabled` setter). */
#include "dw4/reflected.h"
void Gap__Core__igCullFaceAttr__vfunc_32(igCullFaceAttr *self, int mode) {
    self->_mode = mode;
}
