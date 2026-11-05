#include "dw4/reflected.h"

/* 0x0013c5b0
 * Setter: stores the blend-state enable flag (`_enabled`, an igBoolMetaField
 * of the reflected igBlendStateAttr). */
void Gap__Core__igBlendStateAttr__vfunc_32(igBlendStateAttr *self, char enabled) {
    self->_enabled = enabled;
}
