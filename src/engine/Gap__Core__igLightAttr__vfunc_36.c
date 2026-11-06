/* IgLightAttr setter for the light's direction. Copies the caller's three floats into `_direction`
 * and raises `_changed` (the matching position setter is vfunc_35). */
#include "dw4/reflected.h"
void Gap__Core__igLightAttr__vfunc_36(igLightAttr *self, float *direction) {
    /* _direction is reflected as int[3] (igVec3fMetaField); the code moves floats */
    *(float *)&self->_direction[0] = (float) direction[0];
    *(float *)&self->_direction[1] = (float) direction[1];
    *(float *)&self->_direction[2] = (float) direction[2];
    self->_changed = 1;
}
