/* Asks the window's text control to clear one text element: selects TEXTCTL with no named receiver
 * and id -1, appends the element's text type and text name tokens plus the literal CLR, then
 * dispatches SWITCH through the window messenger, reloaded before each call. */
#include "dw4/reflected.h"
extern "C" {
int beMessenger_SelectReceivers(int, int *, int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_AppendString(int, int *);
extern int TEXTCTL_2[4];
extern int SWITCH[4];
extern int CLR[4];
void beNDMWWindow_ClearTextElement(beNDMWWindow *self, int *textType, int *textName) {
    beMessenger_SelectReceivers(self->_messenger, &TEXTCTL_2[0], 0, -1);
    beMessenger_AppendString(self->_messenger, textType);
    beMessenger_AppendString(self->_messenger, textName);
    beMessenger_AppendString(self->_messenger, &CLR[0]);
    beMessenger_DispatchSelected(self->_messenger, &SWITCH[0]);
}
}
