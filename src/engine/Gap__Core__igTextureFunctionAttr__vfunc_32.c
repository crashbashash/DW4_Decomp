/* Setter for `_type`; it also clears `_call_state`, the attribute's per-call state byte, so the
 * new type is applied afresh on the next apply. */
#include "dw4/reflected.h"
void Gap__Core__igTextureFunctionAttr__vfunc_32(igTextureFunctionAttr *self, int type) {
    self->_type = type;
    self->_call_state = 0;
}
