#include "dw4/reflected.h"
extern "C" {
int FUN_001dc870(int);
int FUN_001dc8d0(int);
int FUN_00343430();
int beMessenger_ResolveEnumValue(int, int, int);
int Gap__Bec__beSwitchCtrl__vfunc_33(beSwitchCtrl *arg0, beBaseInfoRam *arg1, int arg2);
}

int Gap__Bec__beSwitchCtrl__vfunc_33(beSwitchCtrl *arg0, beBaseInfoRam *arg1, int arg2) {
    int temp_v0;
    void *temp_s0;

    temp_s0 = (void *)(arg1->_parentInfo);
    temp_v0 = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_00343430(), arg2);
    switch (temp_v0) {
    case 0:
        FUN_001dc870(*(int *)((char *)(temp_s0) + 28));
        return 1;
    case 1:
        FUN_001dc8d0(*(int *)((char *)(temp_s0) + 28));
        return 1;
    default:
        return 0;
    }
}
