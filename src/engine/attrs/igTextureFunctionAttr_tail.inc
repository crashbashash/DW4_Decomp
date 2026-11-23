namespace Gap {
namespace Attrs {

igMultiTextureExt *igTextureFunctionAttr::_extension;
void igTextureFunctionAttr::synchronizeCachedUnitID(igObject *obj)
{
    igTextureFunctionAttr *attr = (igTextureFunctionAttr *)obj;

    attr->setCachedUnitID(attr->_unitID);
}

void igTextureFunctionAttr::setUnitID(short id)
{
    _unitID = id;
    igAttr::setUnitID(id);
}

void igTextureFunctionAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    igAttr::setUnitID((short)_unitID);
}
}
}

void FUN_001412a0(void) {
    *(int *)((char *)(DAT_0055ed08[0]) + 52) = (int)(&TEXTURE_FUNCTION_PSX2_GetMetaEnum);
}

namespace Gap {
namespace Attrs {

void igTextureFunctionAttr::initDefaults()
{
    igVisualAttribute::initDefaults();
    _arg0 = 3;
    _arg1 = 0;
    _type = 2;
    _functionType = 2;
}

void igTextureFunctionAttr::releaseDefaults()
{
    if (igMetaObject_CountInstances(getMeta(), 1) == 0)
        _extension = 0;
    igVisualAttribute::releaseDefaults();
}

void igTextureFunctionAttr::synchronizeDefault(igVisualContext *vc)
{
    _mode = vc->getTextureStageFunc(_unitID);
    if (_extension == 0)
        _extension = (igMultiTextureExt *)vc->getExt("igMultiTextureExt");
}

int igTextureFunctionAttr::getUnitCount(igCapabilityManager *capabilityManager)
{
    return ((igCapabilityManagerDispatchView *)capabilityManager)->getCapability(IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES_PSX2);
}

/* Setter for `_type`; it also clears `_call_state`, the attribute's per-call state byte, so the
 * new type is applied afresh on the next apply. */

void igTextureFunctionAttr::setStageType(int type)
{
    _type = type;
    _call_state = 0;
}

void igTextureFunctionAttr::apply(igVisualContext *vc)
{
    if (_extension != 0) {
        int functionType = _functionType;

        if (_call_state == 2) {
            ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setTextureStageFunc(_unitID, _mode);
            return;
        }
        if (_unitID > 0)
            ((igMultiTextureExtDispatchView *)_extension)->setTextureStageFunction(_unitID, functionType, _mode);
        ((igMultiTextureExtDispatchView *)_extension)->setTextureStageType(_unitID, functionType, _type);
        return;
    }
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setTextureStageFunc(_unitID, _mode);
}
}
}

