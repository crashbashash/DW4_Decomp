/* Asks the model-control's receivers (selected by `ramNo` and `infoName`) whether the named
 * sequence `sqName` is playing: selects the receivers under the "MODELCTRL" message group, appends
 * the sequence name, dispatches the "ISSEQNAME" query and reads back its boolean answer. The
 * caller (Poll, and the load-screen update) polls it until the "SQ_OPEN" sequence has finished. */
#include "dw4/reflected.h"
extern "C" {
int beMessenger_AppendString(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetBool(int, int);
int beMessenger_SelectReceivers(int, int *, int, int);
extern int MODELCTRL[4];
extern int ISSEQNAME[4];
void beNDMWLoadIntf2ComMdlCtrl__IsSequence(beNDMWSaveIntfComMdlCtrl *self, int ramNo, int infoName, int sqName) {
    beMessenger_SelectReceivers(self->_messenger, &MODELCTRL[0], infoName, ramNo);
    beMessenger_AppendString(self->_messenger, sqName);
    beMessenger_DispatchSelected(self->_messenger, &ISSEQNAME[0]);
    beMessenger_GetBool(self->_messenger, 0);
}
}
