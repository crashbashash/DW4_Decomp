#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00587d08[4];
extern int DAT_00588518[4];
extern int DAT_00589208[4];
void Gap__Bec__beTimer__vfunc_23(beTimer *arg0);
}
void Gap__Bec__beTimer__vfunc_23(beTimer *arg0) {
    arg0->_system = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
    arg0->_padManager = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
    arg0->_luaManager = FUN_00236f80(arg0->_insight, DAT_00589208[0]);
}
