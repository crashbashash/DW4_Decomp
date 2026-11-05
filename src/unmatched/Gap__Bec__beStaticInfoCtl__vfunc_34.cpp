#include "dw4/reflected.h"
extern "C" {
int FUN_00343700();
int beMessenger_AppendObject(int, int);
int beMessenger_ResolveEnumValue(int, int, int);
int Gap__Bec__beStaticInfoCtl__vfunc_34(beStaticInfoCtl *arg0, beBaseInfoRam *arg1, beMessengerWork *arg2);
}
int Gap__Bec__beStaticInfoCtl__vfunc_34(beStaticInfoCtl *arg0, beBaseInfoRam *arg1, beMessengerWork *arg2) {
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_00343700(), arg2->_message)) {
    case 0:
        beMessenger_AppendObject(arg0->_messenger, arg0->_staticInfoList);
        goto one;
    default:
        return 0;
    }
one:
    return 1;
}
