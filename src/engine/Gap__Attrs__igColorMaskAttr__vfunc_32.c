/* Setter for the colour write mask: one flag per channel. */
#include "dw4/reflected.h"
void Gap__Attrs__igColorMaskAttr__vfunc_32(igColorMaskAttr *self, char red, char green, char blue, char alpha) {
    self->_red = red;
    self->_green = green;
    self->_blue = blue;
    self->_alpha = alpha;
}
