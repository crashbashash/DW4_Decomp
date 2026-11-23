namespace Gap {
namespace Attrs {

void igFogAttr::apply(igVisualContext *rc)
{
    ((igPsx2VisualContext *)rc)->igPsx2VisualContext::setFogMode((IG_GFX_FOG_MODE)_mode);
    ((igPsx2VisualContext *)rc)->igPsx2VisualContext::setFogDensity(_density);
    ((igPsx2VisualContext *)rc)->igPsx2VisualContext::setFogColor(_color);
    ((igPsx2VisualContext *)rc)->igPsx2VisualContext::setFogNear(_nearVal);
    ((igPsx2VisualContext *)rc)->igPsx2VisualContext::setFogFar(_farVal);
}

void igFogAttr::synchronizeDefault(igVisualContext *vc)
{
    igVec4f color;

    setMode(vc->getFogMode());
    setDensity(vc->getFogDensity());
    vc->getFogColor(color);
    setColor(color);
    setNearFar(vc->getFogNear(), vc->getFogFar());
}
}
}

