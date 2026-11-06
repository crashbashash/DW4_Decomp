#include "dw4/reflected.h"

/* igStackMemoryPool vtable slot 29 (+0x74): constant leaf returning 1. The igArenaMemoryPool and
 * igMallocMemoryPool versions return 0 and igPageMemoryPool returns 1. */
int Gap__Core__igStackMemoryPool__vfunc_29(igStackMemoryPool *self) {
    return 1;
}
