#include "dw4/reflected.h"
/* Byte size of the array field's storage: `_num` elements of 8 bytes each, truncated to 16 bits
 * like the field descriptor's `_size`. */
int Gap__Core__igUnsignedLongArrayMetaField__vfunc_25(igUnsignedLongArrayMetaField *self) {
    return (self->_num * 8) & 0xFFFF;
}
