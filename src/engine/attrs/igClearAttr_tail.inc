namespace Gap {
namespace Attrs {

void igClearAttr::apply(igVisualContext *vc)
{
    unsigned int mode;

    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setClearDepth(getDepth());
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setClearColor(_colorPacked);
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setClearStencil(getStencil());
    mode = getMode();
    if (mode != 0) {
        ((igPsx2VisualContext *)vc)->igPsx2VisualContext::clearRenderDestination(mode);
    }
}

void igClearAttr::synchronizeDefault(igVisualContext *vc)
{
    setStencil(vc->getClearStencil());
    setDepth(vc->getClearDepth());
    _colorPacked = vc->getClearColor();
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

