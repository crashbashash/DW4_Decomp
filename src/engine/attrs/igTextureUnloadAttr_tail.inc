namespace Gap {
namespace Attrs {

void igTextureUnloadAttr::apply(igVisualContext *vc)
{
    igTextureAttr *texture = _texture;

    if (texture != 0) {
        int texId = texture->_texId;

        if (texId != -1)
            ((igPsx2VisualContext *)vc)->igPsx2VisualContext::unloadTexture(texId);
    }
}

void igTextureUnloadAttr::synchronizeCachedUnitID(igObject *obj)
{
    igTextureUnloadAttr *attr = (igTextureUnloadAttr *)obj;

    attr->setCachedUnitID(attr->_unitID);
}

void igTextureUnloadAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    igAttr::setUnitID((short)_unitID);
}

void igTextureUnloadAttr::setUnitID(short id)
{
    _unitID = id;
    igAttr::setUnitID(id);
}

void igTextureUnloadAttr::synchronizeDefault(igVisualContext *vc)
{

}

int igTextureUnloadAttr::getUnitCount(igCapabilityManager *capabilityManager)
{
    return ((igCapabilityManagerDispatchView *)capabilityManager)->getCapability(IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES_PSX2);
}
}
}

