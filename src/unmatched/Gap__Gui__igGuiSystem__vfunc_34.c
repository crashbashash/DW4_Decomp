#include "dw4/reflected.h"
int FUN_004578c0();
extern int DAT_0058c420[4];
int Gap__Gui__igGuiSystem__vfunc_34(igGuiSystem *arg0) {
    int buf[3];

    *(char *)((char *)(arg0->_model) + 180) = 1;
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058c420[0];
    FUN_004578c0(arg0->_model, buf, 1);
    return 1;
}
