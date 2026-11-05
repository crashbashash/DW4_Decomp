#include "dw4/reflected.h"
extern "C" {
int FUN_00236be0(int, beCameraCtrl *);
int FUN_00236c40(int, beCameraCtrl *);
int FUN_00378e40(beCameraCtrl *, int);
int FUN_00378ed0(beCameraCtrl *, beBaseInfoRam *);
int FUN_00379a90(beCameraCtrl *, beBaseInfoRam *);
void Gap__Bec__beCameraCtrl__vfunc_31(beCameraCtrl *arg0, beBaseInfoRam *arg1);
}

void Gap__Bec__beCameraCtrl__vfunc_31(beCameraCtrl *arg0, beBaseInfoRam *arg1) {
    if (arg0->_isFirst != 0) {
        FUN_00236c40(arg0->_insight, arg0);
        FUN_00236be0(arg0->_insight, arg0);
        arg0->_isFirst = 0;
    }
    if (arg1->_isRun != 0) {
        if (FUN_00378e40(arg0, arg1->_parentInfo) != 0) {
            FUN_00378ed0(arg0, arg1);
        } else {
            FUN_00379a90(arg0, arg1);
        }
    }
}
