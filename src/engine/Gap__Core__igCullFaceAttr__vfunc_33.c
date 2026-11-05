#include "dw4/reflected.h"

/* 0x0013caf0
 * Setter: stores the cull-face enable flag (`_enabled`, an igBoolMetaField of
 * the reflected igCullFaceAttr). */
void Gap__Core__igCullFaceAttr__vfunc_33(igCullFaceAttr *self, char enabled) {
    self->_enabled = enabled;
}
