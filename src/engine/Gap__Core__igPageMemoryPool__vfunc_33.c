/* 0x00325d20 -- Gap::Core::igPageMemoryPool::vfunc_33.
 * Reports whether the pool is active: returns _isActive (+112), same slot as igAliasMemoryPool::vfunc_33.  Field name and offset come from the reflected igPageMemoryPool record
 * (include/dw4/reflected.h). */
#include "dw4/reflected.h"
unsigned char Gap__Core__igPageMemoryPool__vfunc_33(igPageMemoryPool *self) {
    return self->_isActive;
}
