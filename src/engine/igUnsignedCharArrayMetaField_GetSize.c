/* 0x0030e650
 * Storage size in bytes of the field's array.  One byte per element, so the
 * size is the element count `_num` (returned as a 16-bit value, like the
 * `_size` field of igMetaField that it feeds).  Compare igLongArrayMetaField
 * and igFloatArrayMetaField, which scale `_num` by the element width. */
#include "dw4/reflected.h"
unsigned short igUnsignedCharArrayMetaField_GetSize(igUnsignedCharArrayMetaField *self) {
    return self->_num;
}
