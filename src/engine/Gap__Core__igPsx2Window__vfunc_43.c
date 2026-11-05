/* 0x00149190 -- Gap::Core::igPsx2Window::vfunc_43.
 * Reports whether the window is open: returns _open (+40).  Field name and offset come from the reflected igPsx2Window record
 * (include/dw4/reflected.h). */
#include "dw4/reflected.h"
unsigned char Gap__Core__igPsx2Window__vfunc_43(igPsx2Window *self) {
    return self->_open;
}
