/* Copy a four-float colour into the light's specular colour and mark the attribute changed
 * (sibling of vfunc_32 for _diffuse and vfunc_33 for _ambient). _specular is reflected as int[4]
 * (igVec4fMetaField) but holds floats. */
#include "dw4/reflected.h"
void Gap__Core__igLightAttr__vfunc_34(igLightAttr *self, float *color) {
    *(float *)&self->_specular[0] = color[0];
    *(float *)&self->_specular[1] = color[1];
    *(float *)&self->_specular[2] = color[2];
    *(float *)&self->_specular[3] = color[3];
    self->_changed = 1;
}
