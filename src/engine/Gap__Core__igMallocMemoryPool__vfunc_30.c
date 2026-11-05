/* 0x003224b0 -- Gap::Core::igMallocMemoryPool::vfunc_30.
 * Empties the pool and marks it active: the 64-bit _size (+136) is cleared and
 * _isActive (+112) set.  Field names come from the reflected igMallocMemoryPool
 * record (include/dw4/reflected.h). */
#include "dw4/reflected.h"
void Gap__Core__igMallocMemoryPool__vfunc_30(igMallocMemoryPool *self) {
    self->_size = 0;
    self->_isActive = 1;
}
