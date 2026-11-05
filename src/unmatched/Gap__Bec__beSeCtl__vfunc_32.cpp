#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00587ea8[4];
void Gap__Bec__beSeCtl__vfunc_32(beSeCtl *arg0);
}
void Gap__Bec__beSeCtl__vfunc_32(beSeCtl *arg0) {
    if (arg0->_sndMng == 0) {
        arg0->_sndMng = FUN_00236f80(arg0->_insight, DAT_00587ea8[0]);
    }
}
