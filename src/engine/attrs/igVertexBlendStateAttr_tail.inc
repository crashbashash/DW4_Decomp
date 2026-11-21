namespace Gap {
namespace Attrs {

void igVertexBlendStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetVertexBlendingState((igPsx2VisualContext *)vc, _enabled);
}

void igVertexBlendStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(((igVisualContextDispatchView *)vc)->getVertexBlendingState());
}

/* Setter for the reflected bool field _enabled. */

void igVertexBlendStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

