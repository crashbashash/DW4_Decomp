/* 0x002dc720: igEnumArrayMetaField virtual getter 25.  Returns the array's
 * storage size in bytes truncated to 16 bits: `_num` elements of 4 bytes each
 * (the enum values are ints).  The 16-bit result matches the reflected
 * `_size` field (unsigned short, +20) that the metafield base class carries. */
#include "dw4/reflected.h"
int Gap__Core__igEnumArrayMetaField__vfunc_25(igEnumArrayMetaField *self) {
    return (self->_num * 4) & 0xFFFF;
}
