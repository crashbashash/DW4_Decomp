/* 0x00301c80: igObjectDirEntry vtable slot 30, a plain getter that returns the reflected
 * field _memoryPoolHandle (include/dw4/reflected.h igObjectDirEntry +44). */
#include "dw4/reflected.h"
int Gap__Core__igObjectDirEntry__vfunc_30(igObjectDirEntry *self) {
    return self->_memoryPoolHandle;
}
