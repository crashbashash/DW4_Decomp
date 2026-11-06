#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00587d08[4];
extern int DAT_00588f38[4];
extern int DAT_00589160[4];
extern int DAT_00589790[4];
extern int DAT_0058a1b8[4];
extern int DAT_0058a1c0[4];
extern int DAT_0058a1c8[4];
extern int DAT_0058a1d0[4];
extern void * DAT_0058a1d8[4];
void Gap__Bec__be__vfunc_23(be *arg0);
}

void Gap__Bec__be__vfunc_23(be *arg0) {
    int temp_v0;

    DAT_0058a1b8[0] = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
    DAT_0058a1c0[0] = FUN_00236f80(arg0->_insight, DAT_00588f38[0]);
    DAT_0058a1c8[0] = FUN_00236f80(arg0->_insight, DAT_00589160[0]);
    temp_v0 = FUN_00236f80(arg0->_insight, DAT_00589790[0]);
    DAT_0058a1d8[0] = (void *)(arg0);
    DAT_0058a1d0[0] = temp_v0;
}
