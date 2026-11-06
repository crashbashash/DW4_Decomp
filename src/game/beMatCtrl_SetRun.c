/* Deferred material activation request. */
#include "dw4/reflected.h"
void beMatCtrl_SetRun(beMatCtrl *self, int value) {
    self->_wkChgFlagNO = self->_wkChkMat;
    self->_wkChgFlag = value;
}
