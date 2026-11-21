namespace Gap {
namespace Attrs {

void igStencilStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetStencilState((igPsx2VisualContext *)vc, _enabled);
}

void igStencilStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(((igVisualContextDispatchView *)vc)->getStencilState());
}

void igStencilStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

