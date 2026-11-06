#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00589208[4];
void Gap__Bec__beGenerater__vfunc_32(beGenerater *arg0);
}
void Gap__Bec__beGenerater__vfunc_32(beGenerater *arg0) {
    if (arg0->_luaManager == 0) {
        arg0->_luaManager = FUN_00236f80(arg0->_insight, DAT_00589208[0]);
        asm { nop } /* matching construct: retail padding nop after the guarded store */
    }
}
