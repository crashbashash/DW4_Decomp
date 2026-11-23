namespace Gap {
namespace Attrs {

void igTextureMatrixStateAttr::synchronizeCachedUnitID(igObject *obj)
{
    igTextureMatrixStateAttr *attr = (igTextureMatrixStateAttr *)obj;

    attr->setCachedUnitID(attr->_unitID);
}

void igTextureMatrixStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetTextureMatrixState((igPsx2VisualContext *)vc, _unitID, _enabled);
}

void igTextureMatrixStateAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    igAttr::setUnitID((short)_unitID);
}

void igTextureMatrixStateAttr::setUnitID(short id)
{
    _unitID = id;
    igAttr::setUnitID(id);
}

void igTextureMatrixStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(vc->getTextureMatrixState(_unitID));
}

/* Setter for the reflected bool field _enabled. */

void igTextureMatrixStateAttr::setState(bool enb)
{
    _enabled = enb;
}

int igTextureMatrixStateAttr::getUnitCount(igCapabilityManager *capabilityManager)
{
    return ((igCapabilityManagerDispatchView *)capabilityManager)->getCapability(IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES_PSX2);
}
}
}

