/* Reset the pool after the base-class reset, restoring _poolOptionFlags to the default registered
 * for that field in igArenaMemoryPool_InitFields (the igMallocMemoryPool counterpart is
 * Gap__Core__igMallocMemoryPool__vfunc_13). */
#include "dw4/reflected.h"
int Gap__Core__igObject__vfunc_11();
extern int g_poolOptionFlagsDefault_004c2370[4];

void Gap__Core__igArenaMemoryPool__vfunc_13(igArenaMemoryPool *self) {
    Gap__Core__igObject__vfunc_11();
    self->_poolOptionFlags = (int) g_poolOptionFlagsDefault_004c2370[0];
}
