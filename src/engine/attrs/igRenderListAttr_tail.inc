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
        _vc->deleteRenderList(_handle);
    _handle = -1;
    _vc = 0;
}
}
}

/* Retail's attrs copy of igVisualContext's inline getScissorType (slot 189), which the igVisualContext and
 * igPsx2VisualContext vtables bind; no attrs code names the member, so the copy stays a C definition. */
int igVisualContext_GetScissorType(igVisualContext *self) {
    return self->_scissorType;
}

