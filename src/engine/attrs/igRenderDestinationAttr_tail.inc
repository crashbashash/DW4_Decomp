/* apply: create the render destination on first use (copying the current one's format unless
 * `_iCreateMode` is 1, or adopting it when 2), then hold the context. */
namespace Gap {
namespace Attrs {

void igRenderDestinationAttr::apply(igVisualContext *vc)
{
    RenderDestinationDesc desc;
    int sizeX;
    int sizeY;

    if (!_bEnabled) {
        return;
    }
    _iPrevRDHandle = igPsx2VisualContext_GetCurrentRenderDestination((igPsx2VisualContext *)vc);
    if (_iRDHandle < 0) {
        if (_iCreateMode != RENDERDESTINATION_CREATE_MODE_AUTONOMOUS) {
            igPsx2VisualContext_GetRenderDestinationSize((igPsx2VisualContext *)vc, _iPrevRDHandle, &sizeX, &sizeY);
            _iSizeX = sizeX;
            _iSizeY = sizeY;
            _iColorBitCount = igPsx2VisualContext_GetColorBitsPerPixel((igPsx2VisualContext *)vc, _iPrevRDHandle);
            _iAlphaBitCount = igPsx2VisualContext_GetAlphaBitsPerPixel((igPsx2VisualContext *)vc, _iPrevRDHandle);
            _iDepthBitCount = igPsx2VisualContext_GetDepthBitsPerPixel((igPsx2VisualContext *)vc, _iPrevRDHandle);
            _iStencilBitCount = igPsx2VisualContext_GetStencilBitsPerPixel((igPsx2VisualContext *)vc, _iPrevRDHandle);
        }
        if (_iCreateMode == RENDERDESTINATION_CREATE_MODE_USE_DEFAULT) {
            _iRDHandle = _iPrevRDHandle;
        } else {
            desc.sizeX = _iSizeX;
            desc.sizeY = _iSizeY;
            desc.colorBitCount = _iColorBitCount;
            desc.alphaBitCount = _iAlphaBitCount;
            desc.depthBitCount = _iDepthBitCount;
            desc.stencilBitCount = _iStencilBitCount;
            desc.type = _iType;
            _iRDHandle = igPsx2VisualContext_CreateRenderDestination((igPsx2VisualContext *)vc, &desc);
        }
    }
    _vc = vc;
}

void igRenderDestinationAttr::synchronizeDefault(igVisualContext *pVC)
{
    int size[2];

    int handle = ((igVisualContextDispatchView *)pVC)->getCurrentRenderDestination();
    _iRDHandle = ((igVisualContextDispatchView *)pVC)->getCurrentRenderDestination();
    _iColorBitCount = ((igVisualContextDispatchView *)pVC)->getColorBitsPerPixel(handle);
    _iAlphaBitCount = ((igVisualContextDispatchView *)pVC)->getAlphaBitsPerPixel(handle);
    _iDepthBitCount = ((igVisualContextDispatchView *)pVC)->getDepthBitsPerPixel(handle);
    _iStencilBitCount = ((igVisualContextDispatchView *)pVC)->getStencilBitsPerPixel(handle);
    ((igVisualContextDispatchView *)pVC)->getRenderDestinationSize(handle, size[0], size[1]);
    setSize(size[0], size[1]);
}

void igRenderDestinationAttr::releaseDefaults()
{
    reset();
    igVisualAttribute::releaseDefaults();
}

void igRenderDestinationAttr::reset()
{
    if (_iCreateMode != RENDERDESTINATION_CREATE_MODE_USE_DEFAULT) {
        if (_vc != 0 && _iRDHandle >= 0) {
            ((igVisualContextDispatchView *)(igVisualContext *)_vc)->deleteRenderDestination(_iRDHandle);
        }
        _vc = 0;
        _iRDHandle = -1;
    }
}
}
}

/* igVisualContext's default for the slot igRenderDestinationAttr's release calls with its handle. */
extern "C" void Gap__Gfx__igVisualContext__destroyRenderDestination(igObject *context, int renderDestination) {
}
