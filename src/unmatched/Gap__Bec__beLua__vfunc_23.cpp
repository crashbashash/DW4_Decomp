/* 0x0038a3a0 — Gap__Bec__beLua__vfunc_23. Banked by tools/retype_struct_member.py (shape: struct3):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
/* reference-counted engine object header: refcount word at +4 */
typedef struct RefCountedHeader { char pad4[4]; int f4; } RefCountedHeader;
extern "C" {
int FUN_00236f80(int, int);
int igObject_Destroy(RefCountedHeader *);
extern int DAT_00587d08[4];
void Gap__Bec__beLua__vfunc_23(beLua *arg0);
}
void Gap__Bec__beLua__vfunc_23(beLua *arg0) {
    RefCountedHeader *temp_a0;
    arg0->_system = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
    temp_a0 = (RefCountedHeader *)(arg0->_luaState);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_luaState = 0;
}
