#include "dw4/reflected.h"

void igObject_Destroy(void *object);
int Gap__Gfx__igPsx2VisualContext__vfunc_77(igObject *context, int type);
void Gap__Gfx__igPsx2VisualContext__vfunc_82(igObject *context, int light, float *color);
void Gap__Gfx__igPsx2VisualContext__vfunc_84(igObject *context, int light, float *color);
void Gap__Gfx__igPsx2VisualContext__vfunc_86(igObject *context, int light, float *color);
void Gap__Gfx__igPsx2VisualContext__vfunc_88(igObject *context, int light, float *position);
void Gap__Gfx__igPsx2VisualContext__vfunc_90(igObject *context, int light, float *direction);
void Gap__Gfx__igPsx2VisualContext__vfunc_92(igObject *context, int light, float cutoff);
void Gap__Gfx__igPsx2VisualContext__vfunc_94(igObject *context, int light, float falloff);
void Gap__Gfx__igPsx2VisualContext__vfunc_96(igObject *context, int light, float *attenuation);

void Gap__Attrs__igLightAttr__vfunc_24(igLightAttr *self, igObject *context) {
    if (self->_lightId == -1) {
        igObject *old;
        self->_lightId = Gap__Gfx__igPsx2VisualContext__vfunc_77(context, self->_lightType);
        if (context) {
            context->_refCount++;
        }
        old = (igObject *)self->_vc;
        if (old) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
        self->_vc = (int)context;
        self->_changed = 1;
    }
    if (!self->_cacheable || self->_changed) {
        Gap__Gfx__igPsx2VisualContext__vfunc_84(context, self->_lightId, self->_ambient);
        Gap__Gfx__igPsx2VisualContext__vfunc_82(context, self->_lightId, self->_diffuse);
        Gap__Gfx__igPsx2VisualContext__vfunc_86(context, self->_lightId, self->_specular);
        switch (self->_lightType) {
        case 1:
            Gap__Gfx__igPsx2VisualContext__vfunc_96(context, self->_lightId, self->_attenuation);
            break;
        case 2:
            Gap__Gfx__igPsx2VisualContext__vfunc_92(context, self->_lightId, self->_cutoff);
            Gap__Gfx__igPsx2VisualContext__vfunc_94(context, self->_lightId, self->_falloff);
            Gap__Gfx__igPsx2VisualContext__vfunc_96(context, self->_lightId, self->_attenuation);
            break;
        }
        self->_changed = 0;
    }
    switch (self->_lightType) {
    case 0:
        Gap__Gfx__igPsx2VisualContext__vfunc_90(context, self->_lightId, self->_direction);
        break;
    case 1:
        Gap__Gfx__igPsx2VisualContext__vfunc_88(context, self->_lightId, self->_position);
        break;
    case 2:
        Gap__Gfx__igPsx2VisualContext__vfunc_90(context, self->_lightId, self->_direction);
        Gap__Gfx__igPsx2VisualContext__vfunc_88(context, self->_lightId, self->_position);
        break;
    }
}
