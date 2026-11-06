/* Reports whether the pool is active: returns _isActive (+112), same slot as
 * igAliasMemoryPool::vfunc_33. Field name and offset come from the reflected igMallocMemoryPool
 * record (include/dw4/reflected.h). */
#include "dw4/reflected.h"
unsigned char Gap__Core__igMallocMemoryPool__vfunc_33(igMallocMemoryPool *self) {
    return self->_isActive;
}
