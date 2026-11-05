#include "dw4/reflected.h"

/* 0x0013c790
 * Setter: stores the clipping-state enable flag (`_enabled`, an igBoolMetaField
 * of the reflected igClippingStateAttr). */
void Gap__Core__igClippingStateAttr__vfunc_32(igClippingStateAttr *self, char enabled) {
    self->_enabled = enabled;
}
