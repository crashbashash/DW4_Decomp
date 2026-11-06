/* Empties the pool and marks it active: the 64-bit _size (+136) is cleared and _isActive (+112)
 * set. */
#include "dw4/reflected.h"
void Gap__Core__igMallocMemoryPool__vfunc_30(igMallocMemoryPool *self) {
    self->_size = 0;
    self->_isActive = 1;
}
