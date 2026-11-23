namespace Gap {
namespace Attrs {

void igNormalizeNormalsStateAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setNormalizeNormalsState(_enabled);
}

void igNormalizeNormalsStateAttr::synchronizeDefault(igVisualContext *vc)
{
    _enabled = vc->getNormalizeNormalsState();
}
}
}

