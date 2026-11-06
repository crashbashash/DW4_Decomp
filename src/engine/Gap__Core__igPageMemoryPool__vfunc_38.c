/* igPageMemoryPool slot 38. igAliasMemoryPool fills the same slot with a getter for its
 * `_alignment`; the page pool reports a fixed 0x1000 (4 KiB, one page). */
#include "dw4/reflected.h"
#define PAGE_POOL_ALIGNMENT 0x1000
int Gap__Core__igPageMemoryPool__vfunc_38(igPageMemoryPool *self) {
    return PAGE_POOL_ALIGNMENT;
}
