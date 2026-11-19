namespace Gap {
namespace Gui {

void igClearRenderer::initializeDrawing() {
    igVisualContextDispatchView *context;

    ((igVisualContextDispatchView *)_visualContext.p)->setClearStencil(0);
    _buffersToClear = 3;
    context = (igVisualContextDispatchView *)_visualContext.p;
    if (context->getStencilBitsPerPixel(context->getCurrentRenderDestination()) > 0) {
        _buffersToClear = _buffersToClear | 4;
    }
}

void igClearRenderer::draw()
{
    ((igVisualContextDispatchView *)_visualContext.p)->clearRenderDestination(_buffersToClear);
}
}
}
