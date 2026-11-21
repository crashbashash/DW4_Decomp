namespace Gap {
namespace Attrs {

void igBlendMatricesAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetBlendingMatrices((igPsx2VisualContext *)vc, _currentMatrixCount, getMatrixArray());
}

void igBlendMatricesAttr::synchronizeDefault(igVisualContext *vc)
{

}
}
}

