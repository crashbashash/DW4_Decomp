namespace Gap {
namespace Attrs {

void igClippingStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetViewportClippingState((igPsx2VisualContext *)vc, _enabled);
}

void igClippingStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(((igVisualContextDispatchView *)vc)->getViewportClippingState());
}

/* Setter: stores the clipping-state enable flag (`_enabled`, an igBoolMetaField of the reflected
 * igClippingStateAttr). */
void igClippingStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

