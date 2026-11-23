namespace Gap {
namespace Attrs {

void igDepthWriteStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetDepthWriteState((igPsx2VisualContext *)vc, _enabled);
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

