namespace Gap {
namespace Gui {

void igClearRenderer::initializeDrawing() {
    igVisualContext *context;

    _visualContext->setClearStencil(0);
    _buffersToClear = 3;
    context = _visualContext;
    if (context->getStencilBitsPerPixel(context->getCurrentRenderDestination()) > 0) {
        _buffersToClear = _buffersToClear | 4;
    }
}

void igClearRenderer::draw()
{
    _visualContext->clearRenderDestination(_buffersToClear);
}
}
}
