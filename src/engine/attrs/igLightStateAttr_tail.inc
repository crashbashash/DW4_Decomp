namespace Gap {
namespace Attrs {

void igLightStateAttr::apply(igVisualContext *vc)
{
    if (_light != 0) {
        if (_light->getHandle() == -1)
            _light->apply(vc);
        igPsx2VisualContext_SetLightState((igPsx2VisualContext *)vc, _light->getHandle(), _enabled);
    }
}

void igLightStateAttr::synchronizeDefault(igVisualContext *vc)
{
    if (_light != 0)
        setState(vc->getLightState(_light->getHandle()));
}

/* Setter for the attribute's reflected _enabled flag. */
void igLightStateAttr::setState(bool enb)
{
    _enabled = enb;
}

void igLightStateAttr::setup(igVisualContext *context)
{
    if (_light != 0)
        _light->setup(context);
}
}
}

