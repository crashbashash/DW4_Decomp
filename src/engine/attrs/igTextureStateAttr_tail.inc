namespace Gap {
namespace Attrs {

void igTextureStateAttr::synchronizeCachedUnitID(igObject *obj)
{
    igTextureStateAttr *attr = (igTextureStateAttr *)obj;

    attr->setCachedUnitID(attr->_unitID);
}

void igTextureStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetTextureStageState((igPsx2VisualContext *)vc, _unitID, _enabled);
}

void igTextureStateAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    igAttr::setUnitID((short)_unitID);
}

void igTextureStateAttr::setUnitID(short id)
{
    _unitID = id;
    igAttr::setUnitID(id);
}

void igTextureStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(((igVisualContextDispatchView *)vc)->getTextureStageState(_unitID));
}

/* Setter for the reflected bool field _enabled. */

void igTextureStateAttr::setState(bool enb)
{
    _enabled = enb;
}

int igTextureStateAttr::getUnitCount(igCapabilityManager *capabilityManager)
{
    return ((igCapabilityManagerDispatchView *)capabilityManager)->getCapability(IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES_PSX2);
}
}
}

