/* 0x00326000: igPageMemoryPool slot 40.  igAliasMemoryPool fills the same slot
 * with a getter for its `_elementSize` (src/engine/Gap__Core__igAliasMemoryPool__vfunc_40.c);
 * the page pool has no fixed element size and returns zero. */
#include "dw4/reflected.h"
int Gap__Core__igPageMemoryPool__vfunc_40(igPageMemoryPool *self) {
    return 0;
}
