/* 0x00323490: reset the pool after the base-class reset, restoring _poolOptionFlags to the
 * default registered for that field in igMallocMemoryPool_InitFields
 * (src/unmatched/igMallocMemoryPool_InitFields.c passes the same word to the field setup). */
#include "dw4/reflected.h"
int Gap__Core__igObject__vfunc_11();
extern int g_poolOptionFlagsDefault_004c25f8[4];
void Gap__Core__igMallocMemoryPool__vfunc_13(igMallocMemoryPool *self) {
    Gap__Core__igObject__vfunc_11();
    self->_poolOptionFlags = (int) g_poolOptionFlagsDefault_004c25f8[0];
}
