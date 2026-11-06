/* Copy a four-float colour into the light's ambient colour and mark the attribute changed (sibling
 * of vfunc_32 for _diffuse and vfunc_34 for _specular). _ambient is reflected as int[4]
 * (igVec4fMetaField) but holds floats. */
#include "dw4/reflected.h"
void Gap__Attrs__igLightAttr__vfunc_33(igLightAttr *self, float *color) {
    *(float *)&self->_ambient[0] = color[0];
    *(float *)&self->_ambient[1] = color[1];
    *(float *)&self->_ambient[2] = color[2];
    *(float *)&self->_ambient[3] = color[3];
    self->_changed = 1;
}
