/* Setter for the spot-light _cutoff (+96); raises _changed (+144) so the cached light state is
 * rebuilt before the next draw. */
#include "dw4/reflected.h"
void Gap__Attrs__igLightAttr__vfunc_37(igLightAttr *self, float cutoff) {
    self->_cutoff = cutoff;
    self->_changed = 1;
}
