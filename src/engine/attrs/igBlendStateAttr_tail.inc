namespace Gap {
namespace Attrs {

void igBlendStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetBlendingState((igPsx2VisualContext *)vc, _enabled);
}

void igBlendStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(((igVisualContextDispatchView *)vc)->getBlendingState());
}

/* Setter: stores the blend-state enable flag (`_enabled`, an igBoolMetaField of the reflected
 * igBlendStateAttr). */
void igBlendStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

