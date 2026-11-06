/* IgPsx2EnvironmentMapShader slot 42: store the reflection amount and clear _configured so the
 * shader is set up again before its next use. */
#include "dw4/reflected.h"
void FUN_001c3070(igPsx2EnvironmentMapShader *self, float reflectionAmount) {
    self->_reflectionAmount = reflectionAmount;
    self->_configured = 0;
}
