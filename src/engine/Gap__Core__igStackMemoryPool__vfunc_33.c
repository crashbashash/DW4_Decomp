/* 0x003276e0 -- Gap::Core::igStackMemoryPool::vfunc_33.
 * Reports whether the pool is active: returns _isActive (+140), same slot as igAliasMemoryPool::vfunc_33.  Field name and offset come from the reflected igStackMemoryPool record
 * (include/dw4/reflected.h). */
#include "dw4/reflected.h"
unsigned char Gap__Core__igStackMemoryPool__vfunc_33(igStackMemoryPool *self) {
    return self->_isActive;
}
