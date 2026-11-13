#include "dw4/reflected.h"

extern "C" void Gap__Bec__beSwitchCtrl__vfunc_32(void);
extern "C" int Gap__Bec__beSwitchCtrl__vfunc_30(void);
extern "C" void Gap__Bec__beSwitchCtrl__vfunc_31(void);
extern "C" int Gap__Bec__beSwitchCtrl__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int igSwitch_EnableAllChildren(int);
extern "C" int igSwitch_DisableAllChildren(int);
extern "C" int FUN_00343430(...);
extern "C" int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int g_beSwitchCtrlInfo_metaObject[4];
extern "C" int g_beSwitchCtrl_metaObject[4];
extern "C" char DAT_0050fab0[];
extern "C" void Gap__Bec__beSwitchCtrl__vfunc_29(beSwitchCtrl * p0, int p1, char * p2);
extern "C" int Gap__Bec__beSwitchCtrl__vfunc_33(beSwitchCtrl *arg0, beBaseInfoRam *arg1, int arg2);

void Gap__Bec__beSwitchCtrl__vfunc_32(void)
{
}

int Gap__Bec__beSwitchCtrl__vfunc_30(void)
{
    return g_beSwitchCtrlInfo_metaObject[0];
}

void Gap__Bec__beSwitchCtrl__vfunc_29(beSwitchCtrl * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_0050fab0);
}

void Gap__Bec__beSwitchCtrl__vfunc_31(void)
{
}

int Gap__Bec__beSwitchCtrl__vfunc_33(beSwitchCtrl *arg0, beBaseInfoRam *arg1, int arg2) {
    int temp_v0;
    void *temp_s0;

    temp_s0 = (void *)(arg1->_parentInfo);
    temp_v0 = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_00343430(), arg2);
    switch (temp_v0) {
    case 0:
        igSwitch_EnableAllChildren(*(int *)((char *)(temp_s0) + 28));
        return 1;
    case 1:
        igSwitch_DisableAllChildren(*(int *)((char *)(temp_s0) + 28));
        return 1;
    default:
        return 0;
    }
}

int Gap__Bec__beSwitchCtrl__vfunc_20(void)
{
    return g_beSwitchCtrl_metaObject[0];
}
