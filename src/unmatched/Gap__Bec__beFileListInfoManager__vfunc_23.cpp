/* 0x0037f260 — Gap__Bec__beFileListInfoManager__vfunc_23. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00587d08[4];
extern int DAT_00588f38[4];
extern int DAT_0058c790[4];
void Gap__Bec__beFileListInfoManager__vfunc_23(beFileListInfoManager *arg0);
}

void Gap__Bec__beFileListInfoManager__vfunc_23(beFileListInfoManager *arg0) {
    arg0->_system = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
    arg0->_messenger = FUN_00236f80(arg0->_insight, DAT_00588f38[0]);
    arg0->_sceneInfoManager = FUN_00236f80(arg0->_insight, DAT_0058c790[0]);
}
