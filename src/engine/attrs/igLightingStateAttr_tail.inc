namespace Gap {
namespace Attrs {

void igLightingStateAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setLightingState(_enabled);
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

