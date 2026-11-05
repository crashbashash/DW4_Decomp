/* 0x003f59b0
 * Ask the window's text control to clear one text element: select TEXTCTL
 * with no named receiver and id -1, append the element's text type and text
 * name tokens plus the literal CLR, then dispatch SWITCH through the window
 * messenger, reloaded before each call (docs/engine/window-presentation.md,
 * "Text close requests"; finding #911). */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_SelectReceivers(int, int *, int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_AppendString(int, int *);
extern int s_TEXTCTL_00518700[4];
extern int s_SWITCH_00518720[4];
extern int s_CLR_00518730[4];
void beNDMWWindow_ClearTextElement(beNDMWWindow *self, int *textType, int *textName) {
    beMessenger_SelectReceivers(self->_messenger, &s_TEXTCTL_00518700[0], 0, -1);
    beMessenger_AppendString(self->_messenger, textType);
    beMessenger_AppendString(self->_messenger, textName);
    beMessenger_AppendString(self->_messenger, &s_CLR_00518730[0]);
    beMessenger_DispatchSelected(self->_messenger, &s_SWITCH_00518720[0]);
}
} /* extern "C" */
