namespace Gap {
namespace Attrs {

void igPolygonModeAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setRenderMode(getMode());
}

void igPolygonModeAttr::synchronizeDefault(igVisualContext *vc)
{
    setMode(vc->getRenderMode());
}

/* Setter for the attribute's reflected _mode enum field (+0x0c); stores the value as given without
 * validation. */

void igPolygonModeAttr::setMode(IG_GFX_RENDER_MODE mode)
{
    _mode = mode;
}
}
}

