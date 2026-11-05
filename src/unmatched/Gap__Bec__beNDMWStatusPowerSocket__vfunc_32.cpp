/* 0x00414640 — Gap__Bec__beNDMWStatusPowerSocket__vfunc_32. Banked by tools/retype_struct_member.py (shape: leadcall0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_00412600(beNDMWStatusPowerSocket *, int, int, int);

void Gap__Bec__beNDMWStatusPowerSocket__vfunc_32(beNDMWStatusPowerSocket *arg0, int arg1) {
    if (arg1 != -1) {
        FUN_00412600(arg0, arg0->_powerSocket, 0, arg1);
    }
}
} /* extern "C" */
