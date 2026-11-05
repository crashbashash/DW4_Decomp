/* 0x002d9410
 * Storage size in bytes of the field's array: `_num` elements of 8 bytes
 * (double), truncated to the 16-bit size the meta field system uses. */
#include "dw4/reflected.h"
int igDoubleArrayMetaField_GetSize(igDoubleArrayMetaField *self) {
    return (self->_num * 8) & 0xFFFF;
}
