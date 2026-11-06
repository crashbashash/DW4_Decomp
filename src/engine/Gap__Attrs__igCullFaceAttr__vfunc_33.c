#include "dw4/reflected.h"

/* Setter: stores the cull-face enable flag (`_enabled`, an igBoolMetaField of the reflected
 * igCullFaceAttr). */
void Gap__Attrs__igCullFaceAttr__vfunc_33(igCullFaceAttr *self, char enabled) {
    self->_enabled = enabled;
}
