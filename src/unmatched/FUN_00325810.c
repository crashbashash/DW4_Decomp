#include "dw4/reflected.h"
int igMemoryPool_CopyConstruct();
extern int DAT_005311f0[4];
void *FUN_00325810(igPageMemoryPool *arg0) {
    igMemoryPool_CopyConstruct();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_005311f0[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}
