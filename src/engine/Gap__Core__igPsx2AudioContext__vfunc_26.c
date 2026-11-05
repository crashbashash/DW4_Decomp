#include "dw4/reflected.h"
int igObject_Destroy();

/* 0x00145b80 — slot 26 of igPsx2AudioContext: set the _window reference (+20).
 * Reference-counted assignment: retain the new object, release the old one
 * (destroying it when its 23-bit count reaches zero, see
 * docs/engine/near-miss-shapes-player-vfunc44.md), then store the new one. */
void Gap__Core__igPsx2AudioContext__vfunc_26(igPsx2AudioContext *self, igObject *window) {
    igObject *previousWindow;
    if (window != 0) {
        window->_refCount = window->_refCount + 1;
    }
    previousWindow = (igObject *)(self->_window);
    if (previousWindow != 0) {
        previousWindow->_refCount = previousWindow->_refCount - 1;
        if ((previousWindow->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousWindow);
        }
    }
    self->_window = (int)window;
}
