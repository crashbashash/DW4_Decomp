/* 0x003e4210
 * Ask the model-control's receivers (selected by `ramNo` and `infoName`) whether
 * the named sequence `sqName` is playing: select the receivers under the
 * "MODELCTRL" message group, append the sequence name, dispatch the "ISSEQNAME"
 * query and read back its boolean answer.  The caller (Poll, and the load-screen
 * update) polls it until the "SQ_OPEN" sequence has finished. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
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
} /* extern "C" */
