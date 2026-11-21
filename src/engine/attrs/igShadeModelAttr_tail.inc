namespace Gap {
namespace Attrs {

void igShadeModelAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetShadingMode((igPsx2VisualContext *)vc, getMode());
}

void igShadeModelAttr::synchronizeDefault(igVisualContext *vc)
{
    setMode(((igVisualContextDispatchView *)vc)->getShadingMode());
}

/* Setter for the reflected _mode field (the shading mode enum). */

void igShadeModelAttr::setMode(IG_GFX_SHADING_MODE m)
{
    _mode = m;
}
}
}

void FUN_00140360(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 36) = arg1;
}

