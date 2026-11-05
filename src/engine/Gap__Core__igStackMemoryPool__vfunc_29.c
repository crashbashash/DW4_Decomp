#include "dw4/reflected.h"

/* 0x00330f80
 * igStackMemoryPool vtable slot 29 (+0x74): constant leaf returning 1.  The sibling pools return 0 for
 * igArenaMemoryPool and igMallocMemoryPool and 1 for igPageMemoryPool, so the slot reads as a per-pool
 * capability flag; which capability is not established. */
int Gap__Core__igStackMemoryPool__vfunc_29(igStackMemoryPool *self) {
    return 1;
}
