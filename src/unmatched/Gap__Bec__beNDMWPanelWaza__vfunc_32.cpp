#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00588518[4];
void Gap__Bec__beNDMWPanelWaza__vfunc_32(beNDMWPanelWaza *arg0) {
    if (arg0->_padManager == 0) {
        arg0->_padManager = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
    }
}
}
