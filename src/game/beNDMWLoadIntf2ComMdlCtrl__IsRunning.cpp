/* 0x003e4480 beNDMWLoadIntf2ComMdlCtrl::IsRunning
 * Asks the common-model controller's messenger whether the model `name` in
 * `slot` is still running: sends the MODELCTRL message ISRUN and returns its
 * boolean reply (docs/engine/common-model-controller.md, cm_is_running;
 * strings "MODELCTRL" 0x5171f8 and "ISRUN" 0x517228). */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_GetBool(int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
extern int MODELCTRL[4];
extern int ISRUN[4];
int beNDMWLoadIntf2ComMdlCtrl__IsRunning(beNDMWLoadIntf2ComMdlCtrl *self, int slot, int name) {
    beMessenger_SendNamed(self->_messenger, &MODELCTRL[0], name, slot, &ISRUN[0]);
    return beMessenger_GetBool(self->_messenger, 0);
}
} /* extern "C" */
