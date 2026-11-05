/* 0x003ecaa0 — beNDMWLoadIntf2MesWin__RequestClose. Banked by tools/retype_struct_member.py (shape: width):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {

int beNDMWLoadIntf2MesWin__RequestMesErase();

void beNDMWLoadIntf2MesWin__RequestClose(beNDMWLoadIntf2MesWin *arg0) {
    beNDMWLoadIntf2MesWin__RequestMesErase();
    arg0->_isWinClose = 1;
}
} /* extern "C" */
