namespace Gap {
namespace Attrs {

void igStencilStateAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setStencilState(_enabled);
}

void igStencilStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(vc->getStencilState());
}

void igStencilStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

