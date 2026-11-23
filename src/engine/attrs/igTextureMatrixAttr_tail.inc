namespace Gap {
namespace Attrs {

void igTextureMatrixAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetTextureMatrixProjectiveState((igPsx2VisualContext *)vc, _unitID, _isProjective);
    igPsx2VisualContext_SetMatrix((igPsx2VisualContext *)vc, _unitID + IG_GFX_MATRIX_STACK_TEXTURE_0, (char *)_m.m);
}

void igTextureMatrixAttr::synchronizeCachedUnitID(igObject *obj)
{
    igTextureMatrixAttr *attr = (igTextureMatrixAttr *)obj;

    attr->setCachedUnitID(attr->_unitID);
}

void igTextureMatrixAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    igAttr::setUnitID((short)_unitID);
}

void igTextureMatrixAttr::setUnitID(short id)
{
    _unitID = id;
    igAttr::setUnitID(id);
}

void igTextureMatrixAttr::synchronizeDefault(igVisualContext *vc)
{
    igMatrix44f m;

    vc->getMatrix((IG_GFX_MATRIX_STACK)(_unitID + IG_GFX_MATRIX_STACK_TEXTURE_0), m);
    setMatrix(m);
    _isProjective = igPsx2VisualContext_GetTextureMatrixProjectiveState((igPsx2VisualContext *)vc, _unitID);
}

void igTextureMatrixAttr::setMatrix(const igMatrix44f &matrix)
{
    igMatrix44f_Copy(_m.m, matrix.m);
}

int igTextureMatrixAttr::getUnitCount(igCapabilityManager *capabilityManager)
{
    return ((igCapabilityManagerDispatchView *)capabilityManager)->getCapability(IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES_PSX2);
}
}
}

