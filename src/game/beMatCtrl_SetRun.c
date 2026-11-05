/* 0x0038ae90 — deferred material activation request.
 * Receiver and fields established by Lua MATsetRun, beMatCtrl construction
 * and reflection; verified byte-identical. Behavioral oracle: findings #859. */
#include "dw4/reflected.h"
void beMatCtrl_SetRun(beMatCtrl *self, int value) {
    self->_wkChgFlagNO = self->_wkChkMat;
    self->_wkChgFlag = value;
}
