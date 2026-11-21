namespace Gap {
namespace Attrs {

void igRenderListAttr::apply(igVisualContext *vc)
{
    int handle = _handle;

    if (handle >= 0)
        igPsx2VisualContext_ExecuteRenderList((igPsx2VisualContext *)vc, handle);
}

void igRenderListAttr::synchronizeDefault(igVisualContext *vc)
{

}

void igRenderListAttr::releaseDefaults()
{
    reset();
    igVisualAttribute::releaseDefaults();
}

void igRenderListAttr::reset()
{
    if (_handle != -1)
        ((igVisualContextDispatchView *)(igVisualContext *)_vc)->deleteRenderList(_handle);
    _handle = -1;
    _vc = 0;
}
}
}

int igVisualContext_GetScissorType(igVisualContext *self) {
    return self->_scissorType;
}

