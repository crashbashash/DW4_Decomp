/* 0x002eff50
 * Accessor: the current read/seek offset into the file's memory buffer
 * (`_iSeekPosition`, +56 in the reflected igMemoryFile). */
#include "dw4/reflected.h"
int Gap__Core__igMemoryFile__vfunc_39(igMemoryFile *self) {
    return self->_iSeekPosition;
}
