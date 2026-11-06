#include "dw4/reflected.h"
int igMemoryPool_Initialize();
extern int DAT_00531030[4];
void *FUN_0031eb90(igArenaMemoryPool *arg0) {
    igMemoryPool_Initialize();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00531030[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}
