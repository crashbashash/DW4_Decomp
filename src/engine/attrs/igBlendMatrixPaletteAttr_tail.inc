namespace Gap {
namespace Attrs {

void igBlendMatrixPaletteAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setBlendingMatrices(_currentMatrixCount, getMatrixArray());
}

/* Empty override of igAttr slot 26 (+0x68). Other attributes use this slot for a per-attribute
 * step (igLightAttr resets its light id, igTimeAttr copies a time from a source object); the
 * blend-matrix palette has none. */
void igBlendMatrixPaletteAttr::synchronizeDefault(igVisualContext *vc)
{

}
}
}

