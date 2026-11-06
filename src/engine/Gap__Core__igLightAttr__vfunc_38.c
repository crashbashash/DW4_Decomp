/* Setter for the spot-light _falloff (+92); raises _changed (+144) so the cached light state is
 * rebuilt before the next draw. */
#include "dw4/reflected.h"
void Gap__Core__igLightAttr__vfunc_38(igLightAttr *self, float falloff) {
    self->_falloff = falloff;
    self->_changed = 1;
}
