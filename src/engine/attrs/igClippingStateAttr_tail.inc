namespace Gap {
namespace Attrs {

void igClippingStateAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setViewportClippingState(_enabled);
}

void igClippingStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(vc->getViewportClippingState());
}

/* Setter: stores the clipping-state enable flag (`_enabled`, an igBoolMetaField of the reflected
 * igClippingStateAttr). */
void igClippingStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

