#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00588f38[4];
void Gap__Bec__beStaticInfoCtl__vfunc_32(beStaticInfoCtl *arg0);
}
void Gap__Bec__beStaticInfoCtl__vfunc_32(beStaticInfoCtl *arg0) {
    if (arg0->_messenger == 0) {
        arg0->_messenger = FUN_00236f80(arg0->_insight, DAT_00588f38[0]);
    }
}
