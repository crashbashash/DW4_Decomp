#include "dw4/reflected.h"
int igObject_InitHeader();
extern int DAT_00528250[4];
void *FUN_001a3d90(igTraversal *arg0) {
    igObject_InitHeader();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00528250[0]);
    arg0->_travProcs = 0;
    return arg0;
}
