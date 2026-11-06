/* Size in bytes of the field's storage: _num vec4f elements of 16 bytes each, truncated to 16 bits
 * like the reflected _size field (unsigned short). */
#include "dw4/reflected.h"
int igVec4fArrayMetaField_GetSize(igVec4fArrayMetaField *self) {
    return (self->_num * 0x10) & 0xFFFF;
}
