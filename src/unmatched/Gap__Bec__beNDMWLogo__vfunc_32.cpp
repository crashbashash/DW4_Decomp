#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00587d08[4];
extern int DAT_00588518[4];
void Gap__Bec__beNDMWLogo__vfunc_32(beNDMWLogo *arg0) {
    if (arg0->_padManager == 0) {
        arg0->_padManager = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
        asm { nop }
    }
    if (arg0->_system_ == 0) {
        arg0->_system_ = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
        asm { nop }
    }
}
}
