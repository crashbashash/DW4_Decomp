#include "dw4/reflected.h"
/* 0x003a52c0 — Gap__Bec__beTimer__vfunc_23. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
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
