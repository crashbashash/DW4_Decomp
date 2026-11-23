namespace Gap {
namespace Attrs {

void igLightingStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetLightingState((igPsx2VisualContext *)vc, _enabled);
}

void igLightingStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(vc->getLightingState());
}

/* Setter for the attribute's reflected _enabled flag; lighting off means unlit geometry. */
void igLightingStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

