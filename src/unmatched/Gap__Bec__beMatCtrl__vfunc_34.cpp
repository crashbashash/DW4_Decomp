#include "dw4/reflected.h"
extern "C" {
int FUN_001dc870(int);
int FUN_001dc8d0(int);
int FUN_0035a6b0();
unsigned int beMessenger_ResolveEnumValue(int, int, int);
int Gap__Bec__beMatCtrl__vfunc_34(beMatCtrl *arg0, beMatCtrlInfoRam *arg1, beMatCtrlInfo *arg2);
}
int Gap__Bec__beMatCtrl__vfunc_34(beMatCtrl *arg0, beMatCtrlInfoRam *arg1, beMatCtrlInfo *arg2) {
    unsigned int temp_v0;
    beMatCtrlInfo *temp_s0;
    temp_s0 = (beMatCtrlInfo *)arg1->_parentInfo;
    temp_v0 = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0035a6b0(), arg2->_dataList);
    switch (temp_v0) {
    case 0:
        FUN_001dc870(temp_s0->_switchgraph);
        goto L;
    case 1:
        FUN_001dc8d0(temp_s0->_switchgraph);
        goto L;
    case 2:
        arg0->_isLuaCallDisp = 1;
        goto L;
    case 3:
        arg0->_isLuaCallDisp = 0;
        goto L;
    case 4:
        arg1->_isRun = 0;
        goto L;
    case 5:
        arg1->_isRun = 1;
        goto L;
    default:
        return 0;
    }
L:
    return 1;
}
