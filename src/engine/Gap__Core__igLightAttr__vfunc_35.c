/* 0x0013ee70 — igLightAttr setter for the light's position.
 * Copies the caller's three floats into `_position` and raises `_changed`
 * (the flag the light-attribute users check before re-uploading the light;
 * the matching direction setter is vfunc_36). */
#include "dw4/reflected.h"
void Gap__Core__igLightAttr__vfunc_35(igLightAttr *self, float *position) {
    /* _position is reflected as int[3] (igVec3fMetaField); the code moves floats */
    *(float *)&self->_position[0] = (float) position[0];
    *(float *)&self->_position[1] = (float) position[1];
    *(float *)&self->_position[2] = (float) position[2];
    self->_changed = 1;
}
