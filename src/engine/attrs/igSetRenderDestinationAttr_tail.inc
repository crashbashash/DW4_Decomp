namespace Gap {
namespace Attrs {

void igSetRenderDestinationAttr::apply(igVisualContext *pVC)
{
    if (_pRDAttr == 0) {
        return;
    }
    if (_pRDAttr->getHandle() < 0) {
        _pRDAttr->apply(pVC);
        if (_pRDAttr->getHandle() < 0) {
            return;
        }
    }
    if (_pRDAttr->getType() == IG_GFX_RENDERDESTINATION_TEXTURE) {
        int texId;

        if (_pRDAttr->getTexture() == 0) {
            return;
        }
        if (_pRDAttr->getTexture()->getSource() != IG_GFX_TEXTURE_SOURCE_BUFFER) {
            _pRDAttr->getTexture()->reset();
            _pRDAttr->getTexture()->setSource(IG_GFX_TEXTURE_SOURCE_BUFFER);
        }
        texId = _pRDAttr->getTexture()->getHandle();
        if (texId > -1) {
            ((igPsx2VisualContext *)pVC)->igPsx2VisualContext::setRenderDestination(_pRDAttr->getHandle(), &texId, 0);
        } else if (_pRDAttr->getTextureCreateMode() == igRenderDestinationAttr::RENDERDESTINATION_TEXTURE_CREATE_MODE_AUTO_CREATE) {
            ((igPsx2VisualContext *)pVC)->igPsx2VisualContext::setRenderDestination(_pRDAttr->getHandle(), &texId, 0);
            _pRDAttr->getTexture()->setHandle(texId);
        }
    } else {
        ((igPsx2VisualContext *)pVC)->igPsx2VisualContext::setRenderDestination(_pRDAttr->getHandle(), 0);
    }
}
}
}

static inline void setDestination(Attr *self, const igSmartPointer<Destination> &destination) {
    Destination *held = destination.get();
    Destination *previous;
    igObject::ref(held);
    previous = self->f12;
    igObject::release(previous);
    self->f12 = held;
}

namespace Gap {
namespace Attrs {

void igSetRenderDestinationAttr::synchronizeDefault(igVisualContext *vc)
{
    if (_pRDAttr == 0) {
        _pRDAttr = igSmartPointer<igRenderDestinationAttr>(igRenderDestinationAttr::_instantiateFromPool(getMemoryPool()));
    }
    _pRDAttr->synchronizeDefault(vc);
}

void igSetRenderDestinationAttr::releaseDefaults()
{
    reset();
    igVisualAttribute::releaseDefaults();
}

void igSetRenderDestinationAttr::reset()
{
    if (_pRDAttr != 0) {
        _pRDAttr->reset();
    }
}
}
}

