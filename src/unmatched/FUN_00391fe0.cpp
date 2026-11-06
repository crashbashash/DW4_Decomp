#include "dw4/reflected.h"
extern "C" {
int beMessenger_SendNamed(int, int *, int, int, int);
extern int DAT_004e0858[4];
extern int DAT_0050eff8[4];
}
extern "C" {
int FUN_00391fe0(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlACTION *arg3);
}
int FUN_00391fe0(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlACTION *arg3) {
    int var_a2;
    int var_a4;
    int t;

    var_a4 = arg3->_name ? arg3->_name : (int)&DAT_004e0858[0];
    t = arg2->_ramNo;
    var_a2 = arg1->_name ? arg1->_name : (int)&DAT_004e0858[0];
    beMessenger_SendNamed(arg0->_messenger, &DAT_0050eff8[0], var_a2, t, var_a4);
    return 1;
}
