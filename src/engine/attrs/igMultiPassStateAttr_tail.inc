namespace Gap {
namespace Attrs {

void igMultiPassStateAttr::apply(igVisualContext *vc)
{
    FUN_001757c0((::igPsx2VisualContext *)vc, _numPasses);
}

void igMultiPassStateAttr::synchronizeDefault(igVisualContext *visualContext)
{
    setNumPasses(((igPsx2VisualContext *)visualContext)->_bMultiPassNum);
}

/* Setter for the pass count (`_numPasses`, +12). */

void igMultiPassStateAttr::setNumPasses(int num)
{
    _numPasses = num;
}
}
}

