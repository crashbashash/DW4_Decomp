/* 0x0013ede0
 * Copy a four-float colour into the light's diffuse colour and mark the
 * attribute changed so the renderer re-applies it.  _diffuse is reflected
 * as int[4] (igVec4fMetaField) but holds floats. */
#include "dw4/reflected.h"
void Gap__Core__igLightAttr__vfunc_32(igLightAttr *self, float *color) {
    *(float *)&self->_diffuse[0] = color[0];
    *(float *)&self->_diffuse[1] = color[1];
    *(float *)&self->_diffuse[2] = color[2];
    *(float *)&self->_diffuse[3] = color[3];
    self->_changed = 1;
}
