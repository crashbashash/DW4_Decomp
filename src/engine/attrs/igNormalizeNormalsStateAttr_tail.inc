namespace Gap {
namespace Attrs {

void igNormalizeNormalsStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetNormalizeNormalsState((igPsx2VisualContext *)vc, _enabled);
}

void igNormalizeNormalsStateAttr::synchronizeDefault(igVisualContext *vc)
{
    _enabled = vc->getNormalizeNormalsState();
}
}
}

