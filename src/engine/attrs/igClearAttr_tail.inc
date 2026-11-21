namespace Gap {
namespace Attrs {

void igClearAttr::apply(igVisualContext *vc)
{
    unsigned int mode;

    igPsx2VisualContext_SetClearDepth((igPsx2VisualContext *)vc, getDepth());
    igPsx2VisualContext_SetClearColorPacked((igPsx2VisualContext *)vc, _colorPacked);
    igPsx2VisualContext_SetClearStencil((igPsx2VisualContext *)vc, getStencil());
    mode = getMode();
    if (mode != 0) {
        igPsx2VisualContext_ClearRenderDestination((igPsx2VisualContext *)vc, mode);
    }
}

void igClearAttr::synchronizeDefault(igVisualContext *vc)
{
    setStencil(((igVisualContextDispatchView *)vc)->getClearStencil());
    setDepth(((igVisualContextDispatchView *)vc)->getClearDepth());
    _colorPacked = ((igVisualContextDispatchView *)vc)->getClearColor();
}

void igClearAttr::initDefaults()
{
    igVisualAttribute::initDefaults();
    _colorPacked = igVec4f_PackColor(_color.vec, 1);
    _depthF = _depth;
}

void igClearAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    _colorPacked = igVec4f_PackColor(_color.vec, 1);
    _depthF = _depth;
}
}
}

