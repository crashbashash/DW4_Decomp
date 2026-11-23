/* apply: create the render destination on first use (copying the current one's format unless
 * `_iCreateMode` is 1, or adopting it when 2), then hold the context. */
namespace Gap {
namespace Attrs {

void igRenderDestinationAttr::apply(igVisualContext *vc)
{
    igRenderDestinationFormat desc;
    int sizeX;
    int sizeY;

    if (!_bEnabled) {
        return;
    }
    _iPrevRDHandle = ((igPsx2VisualContext *)vc)->igPsx2VisualContext::getCurrentRenderDestination();
    if (_iRDHandle < 0) {
        if (_iCreateMode != RENDERDESTINATION_CREATE_MODE_AUTONOMOUS) {
            ((igPsx2VisualContext *)vc)->igPsx2VisualContext::getRenderDestinationSize(_iPrevRDHandle, sizeX, sizeY);
            _iSizeX = sizeX;
            _iSizeY = sizeY;
            _iColorBitCount = ((igPsx2VisualContext *)vc)->igPsx2VisualContext::getColorBitsPerPixel(_iPrevRDHandle);
            _iAlphaBitCount = ((igPsx2VisualContext *)vc)->igPsx2VisualContext::getAlphaBitsPerPixel(_iPrevRDHandle);
            _iDepthBitCount = ((igPsx2VisualContext *)vc)->igPsx2VisualContext::getDepthBitsPerPixel(_iPrevRDHandle);
            _iStencilBitCount = ((igPsx2VisualContext *)vc)->igPsx2VisualContext::getStencilBitsPerPixel(_iPrevRDHandle);
        }
        if (_iCreateMode == RENDERDESTINATION_CREATE_MODE_USE_DEFAULT) {
            _iRDHandle = _iPrevRDHandle;
        } else {
            desc._iWidth = _iSizeX;
            desc._iHeight = _iSizeY;
            desc._iColorBitsPerPixel = _iColorBitCount;
            desc._iAlphaBitsPerPixel = _iAlphaBitCount;
            desc._iDepthBitsPerPixel = _iDepthBitCount;
            desc._iStencilBitsPerPixel = _iStencilBitCount;
            desc._iType = (IG_GFX_RENDERDESTINATION_TYPE)_iType;
            _iRDHandle = ((igPsx2VisualContext *)vc)->igPsx2VisualContext::createRenderDestination(&desc);
        }
    }
    _vc = vc;
}

void igRenderDestinationAttr::synchronizeDefault(igVisualContext *pVC)
{
    int size[2];

    int handle = pVC->getCurrentRenderDestination();
    _iRDHandle = pVC->getCurrentRenderDestination();
    _iColorBitCount = pVC->getColorBitsPerPixel(handle);
    _iAlphaBitCount = pVC->getAlphaBitsPerPixel(handle);
    _iDepthBitCount = pVC->getDepthBitsPerPixel(handle);
    _iStencilBitCount = pVC->getStencilBitsPerPixel(handle);
    pVC->getRenderDestinationSize(handle, size[0], size[1]);
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
            _vc->deleteRenderDestination(_iRDHandle);
        }
        _vc = 0;
        _iRDHandle = -1;
    }
}
}
}

/* igVisualContext's default for the slot igRenderDestinationAttr's release calls with its handle. */
