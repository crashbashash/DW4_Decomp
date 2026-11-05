/* 0x001c3060 — Gap::Sg::igPsx2EnvironmentMapShader::vfunc_41.
 * Setter for `_glossTextureCoordIndex`
 * (gloss-map texture-coordinate set index).  It also clears `_configured`, so the shader's
 * render state is rebuilt on its next use (`_configured` is the shader's
 * built-once flag in include/dw4/reflected.h). */
#include "dw4/reflected.h"
void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_41(igPsx2EnvironmentMapShader *self, int coordIndex) {
    self->_glossTextureCoordIndex = coordIndex;
    self->_configured = 0;
}
