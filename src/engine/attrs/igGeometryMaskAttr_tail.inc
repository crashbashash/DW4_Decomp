namespace Gap {
namespace Attrs {

void igGeometryMaskAttr::apply(igVisualContext *vc)
{
    igVertexComponentFilter mask = getMask();

    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setVertexMask(mask);
}

void igGeometryMaskAttr::synchronizeDefault(igVisualContext *vc)
{
    igVertexComponentFilter mask = vc->getVertexMask();

    _mask = mask;
}
}
}

