namespace Gap {
namespace Attrs {

void igFogStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetFogState((igPsx2VisualContext *)vc, _enabled);
}

void igFogStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(vc->getFogState());
}

void igFogStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

