namespace Gap {
namespace Attrs {

void igGeometryMaskAttr::apply(igVisualContext *vc)
{
    igVertexComponentFilter mask = getMask();

    igPsx2VisualContext_SetVertexMask((igPsx2VisualContext *)vc, (int *)&mask);
}

void igGeometryMaskAttr::synchronizeDefault(igVisualContext *vc)
{
    igVertexComponentFilter mask = ((igVisualContextDispatchView *)vc)->getVertexMask();

    _mask = mask;
}
}
}

