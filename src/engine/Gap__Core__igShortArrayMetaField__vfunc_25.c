/* Storage size in bytes of an array field of _num shorts, truncated to 16 bits. Vtable slot 25 is
 * the element-size query that the aligned array allocation calls through slot 100 and truncates
 * the same way. */
#include "dw4/reflected.h"
int Gap__Core__igShortArrayMetaField__vfunc_25(igShortArrayMetaField *self) {
    return (self->_num * sizeof(short)) & 0xFFFF;
}
