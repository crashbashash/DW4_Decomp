/* 0x00301c70 igObjectDirEntry vtable slot 29: setter for `_memoryPoolHandle` (+44 in
 * include/dw4/reflected.h), the reflected pool handle field of the directory entry.  Slot 30 is
 * the matching getter; igMemoryDirEntry has the same pair. */
#include "dw4/reflected.h"
void Gap__Core__igObjectDirEntry__vfunc_29(igObjectDirEntry *self, int memoryPoolHandle) {
    self->_memoryPoolHandle = memoryPoolHandle;
}
