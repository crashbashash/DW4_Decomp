/* 0x0013eee0 -- Gap::Core::igLightAttr::vfunc_38.
 * Setter for the spot-light _falloff (+92); raises _changed (+144) so the
 * cached light state is rebuilt before the next draw.  Names are the reflected
 * igLightAttr fields (include/dw4/reflected.h, docs/engine/p2-lighting.md). */
#include "dw4/reflected.h"
void Gap__Core__igLightAttr__vfunc_38(igLightAttr *self, float falloff) {
    self->_falloff = falloff;
    self->_changed = 1;
}
