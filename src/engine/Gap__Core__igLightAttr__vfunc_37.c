/* 0x0013eed0 -- Gap::Core::igLightAttr::vfunc_37.
 * Setter for the spot-light _cutoff (+96); raises _changed (+144) so the
 * cached light state is rebuilt before the next draw.  Names are the reflected
 * igLightAttr fields (include/dw4/reflected.h, docs/engine/p2-lighting.md). */
#include "dw4/reflected.h"
void Gap__Core__igLightAttr__vfunc_37(igLightAttr *self, float cutoff) {
    self->_cutoff = cutoff;
    self->_changed = 1;
}
