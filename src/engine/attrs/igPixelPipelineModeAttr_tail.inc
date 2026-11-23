namespace Gap {
namespace Attrs {

void igPixelPipelineModeAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setPixelPipelineMode(_pipelineMode);
}

void igPixelPipelineModeAttr::synchronizeDefault(igVisualContext *vc)
{
    _pipelineMode = vc->getPixelPipelineMode();
}
}
}

/* Stores a float at +0x1c of the receiver. That offset lies past the 20 bytes the reflected
 * igPrimLengthArray1_1 describes, so the store stays an offset write. */
void igPointSpriteExt_SetSpriteSize(igPrimLengthArray1_1 *self, float value) {
    *(float *)((char *)self + 28) = value;
}

