/* Setter for `_glossTextureCoordIndex` (gloss-map texture-coordinate set index). It also clears
 * `_configured`, so the shader's render state is rebuilt on its next use (`_configured` is the
 * shader's built-once flag). */
#include "dw4/reflected.h"
void FUN_001c3060(igPsx2EnvironmentMapShader *self, int coordIndex) {
    self->_glossTextureCoordIndex = coordIndex;
    self->_configured = 0;
}
