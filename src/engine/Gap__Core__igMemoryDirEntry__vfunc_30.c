/* 0x002ef990
 * Accessor: the memory-pool handle this directory entry was allocated from
 * (`_memoryPoolHandle`, +48 in the reflected igMemoryDirEntry). */
#include "dw4/reflected.h"
int Gap__Core__igMemoryDirEntry__vfunc_30(igMemoryDirEntry *self) {
    return self->_memoryPoolHandle;
}
