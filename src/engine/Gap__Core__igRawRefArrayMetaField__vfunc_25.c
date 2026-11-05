/* 0x00305360
 * Storage size in bytes of an array field of _num raw references (4 bytes
 * each), truncated to 16 bits.  Vtable slot 25 is the element-size query
 * (docs/engine/array-storage.md). */
#include "dw4/reflected.h"
int Gap__Core__igRawRefArrayMetaField__vfunc_25(igRawRefArrayMetaField *self) {
    return (self->_num * sizeof(int)) & 0xFFFF;
}
