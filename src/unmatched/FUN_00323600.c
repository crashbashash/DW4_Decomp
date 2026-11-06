#include "dw4/reflected.h"
int igMemoryPool_CopyConstruct();
extern int DAT_00530e90[4];
void *FUN_00323600(igMallocMemoryPool *arg0) {
    igMemoryPool_CopyConstruct();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00530e90[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}
