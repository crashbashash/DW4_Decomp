#include "dw4/reflected.h"
int igMemoryPool_Initialize();
extern int DAT_00530e90[4];
void *FUN_003235c0(igMallocMemoryPool *arg0) {
    igMemoryPool_Initialize();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00530e90[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}
