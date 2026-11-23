namespace Gap {
namespace Attrs {

void igTextureCoordSourceAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetTextureStageCoordSource((igPsx2VisualContext *)vc, _unitID, getMode(), _texCoordIndex);
}

int igTextureCoordSourceAttr::getUnitCount(igCapabilityManager *capabilityManager)
{
    return ((igCapabilityManagerDispatchView *)capabilityManager)->getCapability(IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES_PSX2);
}

void igTextureCoordSourceAttr::synchronizeCachedUnitID(igObject *obj)
{
    igTextureCoordSourceAttr *attr = (igTextureCoordSourceAttr *)obj;

    attr->setCachedUnitID(attr->_unitID);
}

void igTextureCoordSourceAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    igAttr::setUnitID((short)_unitID);
}

void igTextureCoordSourceAttr::setUnitID(short id)
{
    _unitID = id;
    igAttr::setUnitID(id);
}

void igTextureCoordSourceAttr::synchronizeDefault(igVisualContext *vc)
{
    IG_GFX_TEXTURE_COORD_SOURCE source = (IG_GFX_TEXTURE_COORD_SOURCE)_mode;
    int index;

    vc->getTextureStageCoordSource(_unitID, source, index);
    _mode = source;
    _texCoordIndex = index;
}
}
}

