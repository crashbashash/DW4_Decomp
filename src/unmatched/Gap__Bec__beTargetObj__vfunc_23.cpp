#include "dw4/reflected.h"
/* 0x003a5a10 — Gap__Bec__beTargetObj__vfunc_23. hand-matched: a struct member keeps the base pointer where m2c
 * CSE'd arg+N (finding #509's shape); verified byte-identical by tools/verify.py. */
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00587ce8[4];
extern int DAT_00588f38[4];
extern int DAT_0058a570[4];
extern int DAT_0058a578[4];
void Gap__Bec__beTargetObj__vfunc_23(beTargetObj *arg0);
}

void Gap__Bec__beTargetObj__vfunc_23(beTargetObj *arg0) {
    DAT_0058a570[0] = FUN_00236f80(arg0->_insight, DAT_00587ce8[0]);
    DAT_0058a578[0] = FUN_00236f80(arg0->_insight, DAT_00588f38[0]);
}
