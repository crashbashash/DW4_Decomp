/* Setter for the cull mode (`_mode`, +16); slot 33 is the matching `_enabled` setter. */
#include "dw4/reflected.h"
void Gap__Core__igCullFaceAttr__vfunc_32(igCullFaceAttr *self, int mode) {
    self->_mode = mode;
}
