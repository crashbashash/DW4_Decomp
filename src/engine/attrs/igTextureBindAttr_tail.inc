int g_igTextureBindAttr_applySlotFast;
int g_igTextureBindAttr_applySlotDefault;
namespace Gap {
namespace Attrs {

int igTextureBindAttr::getUnitCount(igCapabilityManager *capabilityManager)
{
    return ((igCapabilityManagerDispatchView *)capabilityManager)->getCapability(IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES_PSX2);
}

/* Empty leaf in igTextureBindAttr vtable slot 26 (+0x68): a do-nothing default for a virtual this
 * attribute does not need. */
void igTextureBindAttr::synchronizeDefault(igVisualContext *vc)
{

}

void igTextureBindAttr::reset()
{
    if (_texture != 0) {
        _texture->reset();
    }
}

void igTextureBindAttr::setup(igVisualContext *context)
{
    if (_texture != 0) {
        _texture->setup(context);
    }
}

void igTextureBindAttr::applyFast(igVisualContext *vc)
{
    igTextureAttr *texture = _texture;

    igPsx2VisualContext_SetTexture((igPsx2VisualContext *)vc, texture ? texture->getHandle() : -1, _unitID);
}

void igTextureBindAttr::apply(igVisualContext *vc)
{
    int texId;

    if (_texture == 0) {
        igPsx2VisualContext_SetTexture((igPsx2VisualContext *)vc, -1, _unitID);
        return;
    }
    _texture->apply(vc);
    texId = _texture->getHandle();
    if (texId >= 0) {
        igPsx2VisualContext_SetTexture((igPsx2VisualContext *)vc, texId, _unitID);
    }
}

void igTextureBindAttr::synchronizeCachedUnitID(igObject *obj)
{
    igTextureBindAttr *attr = (igTextureBindAttr *)obj;

    attr->setCachedUnitID(attr->_unitID);
}

void igTextureBindAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    igAttr::setUnitID((short)_unitID);
}

void igTextureBindAttr::setUnitID(short id)
{
    _unitID = id;
    igAttr::setUnitID(id);
}
}
}

void igTextureBindAttr_SetFastApply(int arg0) {
    /* matching construct: cxx_sweep — sp10 and sp0 initialised at their declarations, sp0 declared inside the if */
    V3 sp10 = { 0, 0x60, 0.0f };
    int var_a1;
    int idx;
    int temp_a4;
    temp_a4 = *(int *)((char *)(Gap::Attrs::igTextureBindAttr::getClassMeta()) + 92);
    idx = sp10.b;
    if (g_igTextureBindAttr_slotsCached == 0) {
        g_igTextureBindAttr_applySlotDefault = *(int *)(temp_a4 + idx);
        V3 sp0 = { 0, 0x80, 0.0f };
        g_igTextureBindAttr_applySlotFast = *(int *)(temp_a4 + sp0.b);
        g_igTextureBindAttr_slotsCached = 1;
    }
    if (arg0 != 0) {
        var_a1 = g_igTextureBindAttr_applySlotFast;
    } else {
        var_a1 = g_igTextureBindAttr_applySlotDefault;
    }
    *(int *)(temp_a4 + idx) = var_a1;
    g_igTextureBindAttr_fastApplyEnabled = arg0;
}

namespace Gap {
namespace Attrs {

void igTextureBindAttr::userRegister()
{
    unsigned char enable;

    enable = 0;
    ((igRegistry *)(*(int *)((char *)g_objectSystem + 56)))->getValue(7, "enableIgTextureAttrFastApply", enable, 0, 0);
    igTextureBindAttr_SetFastApply(enable);
}
}
}

