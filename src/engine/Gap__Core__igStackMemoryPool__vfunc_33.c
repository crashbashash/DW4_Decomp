/* Reports whether the pool is active: returns _isActive (+140), same slot as
 * igAliasMemoryPool::vfunc_33. */
#include "dw4/reflected.h"
unsigned char Gap__Core__igStackMemoryPool__vfunc_33(igStackMemoryPool *self) {
    return self->_isActive;
}
