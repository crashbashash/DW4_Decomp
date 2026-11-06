/* Reset a light attribute to its unassigned state: no hardware light id (-1), flagged changed and
 * cacheable so the next apply re-uploads it. */
#include "dw4/reflected.h"
void Gap__Core__igLightAttr__vfunc_26(igLightAttr *self) {
    self->_lightId = -1;
    self->_changed = 1;
    self->_cacheable = 1;
}
