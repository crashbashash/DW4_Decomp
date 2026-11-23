namespace Gap {
namespace Attrs {

void igTextureMatrixAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->setTextureMatrixProjectiveState(_unitID, _isProjective);
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setMatrix((IG_GFX_MATRIX_STACK)(_unitID + IG_GFX_MATRIX_STACK_TEXTURE_0), _m);
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
    _isProjective = ((igPsx2VisualContext *)vc)->getTextureMatrixProjectiveState(_unitID);
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

