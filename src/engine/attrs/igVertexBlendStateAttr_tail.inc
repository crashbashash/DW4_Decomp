namespace Gap {
namespace Attrs {

void igVertexBlendStateAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setVertexBlendingState(_enabled);
}

void igVertexBlendStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(vc->getVertexBlendingState());
}

/* Setter for the reflected bool field _enabled. */

void igVertexBlendStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

