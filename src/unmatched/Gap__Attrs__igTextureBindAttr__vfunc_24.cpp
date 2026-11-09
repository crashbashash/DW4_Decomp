#include "dw4/reflected.h"

extern "C" {
void Gap__Gfx__igPsx2VisualContext__vfunc_127(void *context, int texId, int unitID);
void Gap__Attrs__igTextureBindAttr__vfunc_24(igTextureBindAttr *attr, void *context);
}

class igTextureAttrView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void prepare();
};

void Gap__Attrs__igTextureBindAttr__vfunc_24(igTextureBindAttr *attr, void *context) {
    igTextureAttrView *texture = (igTextureAttrView *)attr->_texture;
    int texId;
    if (texture == 0) {
        Gap__Gfx__igPsx2VisualContext__vfunc_127(context, -1, attr->_unitID);
        return;
    }
    texture->prepare();
    texId = ((igTextureAttr *)attr->_texture)->_texId;
    if (texId >= 0) {
        Gap__Gfx__igPsx2VisualContext__vfunc_127(context, texId, attr->_unitID);
    }
}
