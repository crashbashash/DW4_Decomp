#include "dw4/reflected.h"
/* Byte size of the array field's storage: `_num` elements of 2 bytes each, truncated to 16 bits
 * like the field descriptor's `_size`. */
int Gap__Core__igUnsignedShortArrayMetaField__vfunc_25(igUnsignedShortArrayMetaField *self) {
    return (self->_num * 2) & 0xFFFF;
}
