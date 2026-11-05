/* 0x0030e7f0
 * Size in bytes of the array field: `_num` unsigned-int elements, truncated to
 * the 16-bit `_size` field width of the meta-field (reflected.h
 * igUnsignedIntArrayMetaField: `_num` +52, `_size` +20 unsigned short). */
#include "dw4/reflected.h"
int Gap__Core__igUnsignedIntArrayMetaField__vfunc_25(igUnsignedIntArrayMetaField *self) {
    return (self->_num * sizeof(unsigned int)) & 0xFFFF;
}
