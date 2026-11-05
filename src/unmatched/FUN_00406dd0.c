/* 0x00406dd0 — FUN_00406dd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_00406dd0(beNDMWGameRam *arg0, int arg1) {
    return *(int *)(arg0->_system + (arg1 * 4));
}
