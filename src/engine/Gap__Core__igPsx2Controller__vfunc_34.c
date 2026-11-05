/* 0x00149300 -- Gap::Core::igPsx2Controller::vfunc_34.
 * Reports whether the controller is connected: returns _connected (+52).  Field name and offset come from the reflected igPsx2Controller record
 * (include/dw4/reflected.h). */
#include "dw4/reflected.h"
unsigned char Gap__Core__igPsx2Controller__vfunc_34(igPsx2Controller *self) {
    return self->_connected;
}
