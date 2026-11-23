namespace Gap {
namespace Attrs {

void igMatrixOptStateAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->setMatrixOptimizationState(_enabled);
}

void igMatrixOptStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(((igPsx2VisualContext *)vc)->getMatrixOptimizationState());
}

/* Setter for the attribute's reflected _enabled flag. */
void igMatrixOptStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

