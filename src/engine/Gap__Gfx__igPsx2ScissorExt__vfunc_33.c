/* Getter for the scissor rectangle: origin and size into the four out parameters. */
#include "dw4/reflected.h"
void Gap__Gfx__igPsx2ScissorExt__vfunc_33(igPsx2ScissorExt *self, int *originX, int *originY, int *width, int *height) {
    *originX = self->_scissorOrgX;
    *originY = self->_scissorOrgY;
    *width = self->_scissorWidth;
    *height = self->_scissorHeight;
}
