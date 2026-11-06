/* Getter: the pool's _rawMemory reference (+116, reflected as igRawRefMetaField), the backing
 * block the stack pointer walks through. */
#include "dw4/reflected.h"
int Gap__Core__igStackMemoryPool__vfunc_26(igStackMemoryPool *self) {
    return self->_rawMemory;
}
