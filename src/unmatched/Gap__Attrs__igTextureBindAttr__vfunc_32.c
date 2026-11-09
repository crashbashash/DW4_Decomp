#include "dw4/reflected.h"

void Gap__Gfx__igPsx2VisualContext__vfunc_127(void *context, int texId, int unitID);

void Gap__Attrs__igTextureBindAttr__vfunc_32(igTextureBindAttr *attr, void *context) {
    igTextureAttr *texture = (igTextureAttr *)attr->_texture;
    Gap__Gfx__igPsx2VisualContext__vfunc_127(context, texture ? texture->_texId : -1, attr->_unitID);
}
