/* Asks the common-model controller's messenger whether the model `name` in `slot` is still
 * running: sends the MODELCTRL message ISRUN and returns its boolean reply. */
#include "dw4/reflected.h"
extern "C" {
int beMessenger_GetBool(int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
extern int MODELCTRL[4];
extern int ISRUN[4];
int beNDMWLoadIntf2ComMdlCtrl__IsRunning(beNDMWLoadIntf2ComMdlCtrl *self, int slot, int name) {
    beMessenger_SendNamed(self->_messenger, &MODELCTRL[0], name, slot, &ISRUN[0]);
    return beMessenger_GetBool(self->_messenger, 0);
}
}
