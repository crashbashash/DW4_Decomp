namespace Gap {
namespace Attrs {

void igFogAttr::apply(igVisualContext *rc)
{
    igPsx2VisualContext_SetFogMode((igPsx2VisualContext *)rc, (IG_GFX_FOG_MODE)_mode);
    igPsx2VisualContext_SetFogDensity((igPsx2VisualContext *)rc, _density);
    igPsx2VisualContext_SetFogColor((igPsx2VisualContext *)rc, &_color);
    igPsx2VisualContext_SetFogNear((igPsx2VisualContext *)rc, _nearVal);
    igPsx2VisualContext_SetFogFar((igPsx2VisualContext *)rc, _farVal);
}

void igFogAttr::synchronizeDefault(igVisualContext *vc)
{
    igVec4f color;

    setMode(((igVisualContextDispatchView *)vc)->getFogMode());
    setDensity(((igVisualContextDispatchView *)vc)->getFogDensity());
    ((igVisualContextDispatchView *)vc)->getFogColor(color);
    setColor(color);
    setNearFar(((igVisualContextDispatchView *)vc)->getFogNear(), ((igVisualContextDispatchView *)vc)->getFogFar());
}
}
}

