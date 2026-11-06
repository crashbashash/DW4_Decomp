/* Reset the pool after the base-class reset, restoring _poolOptionFlags to the default registered
 * for that field in igMallocMemoryPool_InitFields. */
#include "dw4/reflected.h"
int Gap__Core__igObject__vfunc_11();
extern int g_poolOptionFlagsDefault_004c25f8[4];
void Gap__Core__igMallocMemoryPool__vfunc_13(igMallocMemoryPool *self) {
    Gap__Core__igObject__vfunc_11();
    self->_poolOptionFlags = (int) g_poolOptionFlagsDefault_004c25f8[0];
}
