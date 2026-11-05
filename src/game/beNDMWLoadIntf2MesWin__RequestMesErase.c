/* 0x003ecb90 — beNDMWLoadIntf2MesWin__RequestMesErase. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver is a beNDMWLoadIntf2MesWin (same receiver as beNDMWLoadIntf2MesWin__RequestOpen, which
 * clears the bool block at +28..+34; callers beNDMWLoadIntf2MesWin__Update and the SaveIntf /
 * LoadIntf2 vfunc_31 bodies pass the message window): +32 _isMesErase and
 * +33 _isMesCom are the two bool fields at those offsets. */
#include "dw4/reflected.h"

void beNDMWLoadIntf2MesWin__RequestMesErase(beNDMWLoadIntf2MesWin *arg0) {
    arg0->_isMesErase = 1;
    arg0->_isMesCom = 1;
}
