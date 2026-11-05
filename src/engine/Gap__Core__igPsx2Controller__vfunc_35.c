/* 0x00149310: igPsx2Controller vtable slot 35, a plain getter that returns the reflected
 * field _attachedWindow (the window the controller is attached to, include/dw4/reflected.h
 * igPsx2Controller +32). */
#include "dw4/reflected.h"
int Gap__Core__igPsx2Controller__vfunc_35(igPsx2Controller *self) {
    return self->_attachedWindow;
}
