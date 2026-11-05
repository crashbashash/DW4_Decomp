/* 0x002ef980 igMemoryDirEntry vtable slot 29: field-store leaf.  Stores its argument into
 * the reflected `_memoryPoolHandle` field (+48, igIntMetaField in include/dw4/reflected.h),
 * so it acts as the pool-handle setter of the directory entry. */
#include "dw4/reflected.h"
void Gap__Core__igMemoryDirEntry__vfunc_29(igMemoryDirEntry *self, int memoryPoolHandle) {
    self->_memoryPoolHandle = memoryPoolHandle;
}
