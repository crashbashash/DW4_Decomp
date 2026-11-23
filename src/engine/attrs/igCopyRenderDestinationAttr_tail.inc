namespace Gap {
namespace Attrs {

void igCopyRenderDestinationAttr::apply(igVisualContext *pVC)
{
    int handle;

    if (_pRDAttr != 0) {
        handle = _pRDAttr->getHandle();
    } else {
        handle = pVC->getCurrentRenderDestination();
    }
    switch (_copyType) {
    case FROM_RENDERDESTINATION_TO_TEXTURE:
        if (_pTextureAttr->getHandle() < 0) {
            _pTextureAttr->apply(pVC);
        }
        ((igPsx2VisualContext *)pVC)->igPsx2VisualContext::copyRenderDestinationToTexture(handle, _pTextureAttr->getHandle(), _sourceX, _sourceY, _sizeW, _sizeH, _destinationX, _destinationY);
        return;
    case FROM_RENDERDESTINATION_TO_MEMORY:
        ((igPsx2VisualContext *)pVC)->igPsx2VisualContext::copyRenderDestinationToMemory(handle, (igImage *)_pImage, _sourceX, _sourceY, _sizeW, _sizeH);
        break;
    case NOT_SET:
        break;
    case FROM_RENDERDESTINATION_DEPTH_TO_TEXTURE:
    case FROM_RENDERDESTINATION_DEPTH_TO_MEMORY:
        break;
    default:
        break;
    }
}

/* Empty override of attribute vtable slot 26, which igLightAttr implements as a reset to the
 * unassigned state: the copy-render-destination attribute has nothing to reset here. */
void igCopyRenderDestinationAttr::synchronizeDefault(igVisualContext *vc)
{

}
}
}

