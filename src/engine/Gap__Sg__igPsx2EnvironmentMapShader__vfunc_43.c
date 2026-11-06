/* Setter for `_isTransparent` (transparency flag). It also clears `_configured`, so the shader's
 * render state is rebuilt on its next use (`_configured` is the shader's built-once flag in
 * include/dw4/reflected.h). */
#include "dw4/reflected.h"
void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_43(igPsx2EnvironmentMapShader *self, char isTransparent) {
    self->_isTransparent = isTransparent;
    self->_configured = 0;
}
