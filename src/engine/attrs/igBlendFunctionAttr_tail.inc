namespace Gap {
namespace Attrs {

igBlendEquationExt *igBlendFunctionAttr::_extension;
void igBlendFunctionAttr::releaseDefaults()
{
    if (igMetaObject_CountInstances(getMeta(), 1) == 0)
        _extension = 0;
    igVisualAttribute::releaseDefaults();
}

void igBlendFunctionAttr::apply(igVisualContext *vc)
{
    FUN_00174510((::igPsx2VisualContext *)vc, getSource(), getDestination(), _blendConstant, _blendStage);
    if (_extension != 0) {
        _extension->_equation = _eq;
        igPsx2BlendEquationExt_SetBlendFactors((igPsx2BlendEquationExt *)_extension, _blendA, _blendB, _blendC, _blendD,
                                               (char)_blendConstant);
        ((igBlendEquationExtDispatchView *)_extension)->applyEquation();
    }
}

void igBlendFunctionAttr::synchronizeDefault(igVisualContext *vc)
{
    setSource(vc->getBlendingSource());
    setDestination(vc->getBlendingDestination());
    if (_extension == 0)
        _extension = (igBlendEquationExt *)vc->getExt("igBlendEquationExt");
}

/* Setter for the destination blend factor (`_dst`, +16); `_src` at +12 is the source factor. */

void igBlendFunctionAttr::setDestination(IG_GFX_BLENDING_FUNCTION d)
{
    _dst = d;
}

void igBlendFunctionAttr::setSource(IG_GFX_BLENDING_FUNCTION s)
{
    _src = s;
}

void igBlendFunctionAttr::synchronizeCachedUnitID(igObject *obj)
{
    igBlendFunctionAttr *attr = (igBlendFunctionAttr *)obj;

    attr->setCachedUnitID(attr->_blendStage);
}

void igBlendFunctionAttr::setUnitID(short id)
{
    _blendStage = id;
    igAttr::setUnitID(id);
}

void igBlendFunctionAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    igAttr::setUnitID((short)_blendStage);
}

void igBlendFunctionAttr::constantChanged(igObject *obj)
{
    igBlendFunctionAttr *attr = (igBlendFunctionAttr *)obj;

    attr->_blendConstant = (unsigned int)(128.0f * attr->_blendConstantFloat);
}

int igBlendFunctionAttr::getUnitCount(igCapabilityManager *capabilityManager)
{
    return ((igCapabilityManagerDispatchView *)capabilityManager)->getCapability(IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES_PSX2);
}
}
}

