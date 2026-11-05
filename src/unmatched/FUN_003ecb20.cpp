#include "dw4/reflected.h"
/* 0x003ecb20 — FUN_003ecb20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver: beNDMWLoadIntf2MesWin (+16 _messenger, +34 _isCtrl, +44 _ramNo). */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_SendNamed(int, int *, int *, int, int *);
int beNDMWLoadIntf2MesWin__RequestMesErase(beNDMWLoadIntf2MesWin *);
extern int DAT_00517a48[4];
extern int DAT_00517a60[4];
extern int DAT_00517af0[4];
void FUN_003ecb20(beNDMWLoadIntf2MesWin *arg0) {
    arg0->_isCtrl = 0;
    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00517a60[0], arg0->_ramNo, &DAT_00517af0[0]);
    beNDMWLoadIntf2MesWin__RequestMesErase(arg0);
}
} /* extern "C" */
