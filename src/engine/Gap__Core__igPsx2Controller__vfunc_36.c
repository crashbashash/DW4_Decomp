#include "dw4/reflected.h"
int igObject_Destroy();

/* slot 36 of igPsx2Controller: set the _attachedWindow reference (+32). Reference-counted
 * assignment: retain the new object, release the old one (destroying it when its 23-bit count
 * reaches zero), then store the new one. */
void Gap__Core__igPsx2Controller__vfunc_36(igPsx2Controller *self, igObject *window) {
    igObject *previousWindow;
    if (window != 0) {
        window->_refCount = window->_refCount + 1;
    }
    previousWindow = (igObject *)(self->_attachedWindow);
    if (previousWindow != 0) {
        previousWindow->_refCount = previousWindow->_refCount - 1;
        if ((previousWindow->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousWindow);
        }
    }
    self->_attachedWindow = (int)window;
}
