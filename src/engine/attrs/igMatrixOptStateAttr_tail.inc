namespace Gap {
namespace Attrs {

void igMatrixOptStateAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetMatrixOptimizationState((igPsx2VisualContext *)vc, _enabled);
}

void igMatrixOptStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(igPsx2VisualContext_GetMatrixOptimizationState((igPsx2VisualContext *)vc));
}

/* Setter for the attribute's reflected _enabled flag. */
void igMatrixOptStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

