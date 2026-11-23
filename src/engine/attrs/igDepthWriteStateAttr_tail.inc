namespace Gap {
namespace Attrs {

void igDepthWriteStateAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setDepthWriteState(_enabled);
}

void igDepthWriteStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(vc->getDepthWriteState());
}

/* Setter for the attribute's reflected _enabled flag. */
void igDepthWriteStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

