#include "dw4/reflected.h"
int FUN_001c5d10();
int FUN_00453e70();
int FUN_004540d0();

void Gap__Gui__igDefaultAspect__vfunc_25(igDefaultAspect *arg0) {
    int i;
    void *l;

    for (i = 0; l = (void *)arg0->_elementList, i < *(int *)((char *)l + 8); i++) {
        FUN_001c5d10(arg0->_node, *(int *)((char *)((*(int *)(*(int *)((char *)l + 16) + (i * 4)))) + 16));
    }
    FUN_004540d0(arg0);
    FUN_00453e70(arg0);
}
