#include "dw4/reflected.h"
/* Setter for the attribute's reflected _enabled flag; lighting off means unlit geometry. */
void Gap__Core__igLightingStateAttr__vfunc_32(igLightingStateAttr *self, char enabled) {
    self->_enabled = enabled;
}
