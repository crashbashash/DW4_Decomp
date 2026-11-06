/* Storage size in bytes of the field's array: `_num` elements of 8 bytes (long), truncated to the
 * 16-bit size the meta field system uses. */
#include "dw4/reflected.h"
int igLongArrayMetaField_GetSize(igLongArrayMetaField *self) {
    return (self->_num * 8) & 0xFFFF;
}
