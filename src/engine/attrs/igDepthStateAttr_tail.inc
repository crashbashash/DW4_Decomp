namespace Gap {
namespace Attrs {

void igDepthStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(vc->getDepthTestState());
}

/* Setter for the attribute's reflected _enabled flag. */
void igDepthStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}

void igDepthStateAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setDepthTestState(_enabled);
}
}
}

