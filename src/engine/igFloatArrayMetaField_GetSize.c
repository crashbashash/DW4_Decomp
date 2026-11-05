/* 0x002e36b0
 * Storage size in bytes of the field's array: `_num` elements of 4 bytes
 * (float), truncated to the 16-bit size the meta field system uses. */
#include "dw4/reflected.h"
int igFloatArrayMetaField_GetSize(igFloatArrayMetaField *self) {
    return (self->_num * 4) & 0xFFFF;
}
