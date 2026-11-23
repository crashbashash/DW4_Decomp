namespace Gap {
namespace Attrs {

void igCullFaceAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(vc->getCullFaceState());
    setMode(vc->getCullFaceMode());
}

/* Setter for the cull mode (`_mode`, +16); slot 33 is the matching `_enabled` setter. */

void igCullFaceAttr::setMode(IG_GFX_CULL_FACE_MODE m)
{
    _mode = m;
}

/* Setter: stores the cull-face enable flag (`_enabled`, an igBoolMetaField of the reflected
 * igCullFaceAttr). */
void igCullFaceAttr::setState(bool enabled)
{
    _enabled = enabled;
}

void igCullFaceAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetCullFaceState((igPsx2VisualContext *)vc, _enabled);
    igPsx2VisualContext_SetCullFaceMode((igPsx2VisualContext *)vc, getMode());
}
}
}

