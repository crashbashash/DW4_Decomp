namespace Gap {
namespace Attrs {

void igBlendMatricesAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setBlendingMatrices(_currentMatrixCount, getMatrixArray());
}

void igBlendMatricesAttr::synchronizeDefault(igVisualContext *vc)
{

}
}
}

