namespace Gap {
namespace Attrs {

void igVertexBlendMatrixAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetMatrix((igPsx2VisualContext *)vc, _blendMatID + IG_GFX_MATRIX_STACK_VERTEX_BLEND_0, (char *)_m.m);
}

void igVertexBlendMatrixAttr::synchronizeCachedUnitID(igObject *obj)
{
    igVertexBlendMatrixAttr *attr = (igVertexBlendMatrixAttr *)obj;

    attr->setCachedUnitID(attr->_blendMatID);
}

void igVertexBlendMatrixAttr::setUnitID(short id)
{
    _blendMatID = id;
    igAttr::setUnitID(id);
}

void igVertexBlendMatrixAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    igAttr::setUnitID((short)_blendMatID);
}

void igVertexBlendMatrixAttr::synchronizeDefault(igVisualContext *vc)
{
    igMatrix44f m;

    ((igVisualContextDispatchView *)vc)->getMatrix((IG_GFX_MATRIX_STACK)(_blendMatID + IG_GFX_MATRIX_STACK_VERTEX_BLEND_0), m);
    setMatrix(m);
}

void igVertexBlendMatrixAttr::setMatrix(const igMatrix44f &matrix)
{
    igMatrix44f_Copy(_m.m, matrix.m);
}

int igVertexBlendMatrixAttr::getUnitCount(igCapabilityManager *capabilityManager)
{
    return ((igCapabilityManagerDispatchView *)capabilityManager)->getCapability(IG_GFX_CAPABILITY_MAX_VERTEX_BLEND_MATRICES);
}
}
}

static inline bool InRange(float x, float lo, float hi) {
    return x >= lo && x <= hi;
}

