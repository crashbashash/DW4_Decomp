namespace Gap {
namespace Attrs {

void igStencilFunctionAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setStencilOps(_stenFailOp, _stenPassZPassOp, _stenPassZFailOp);
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setStencilRefVal(_refVal);
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setStencilFunc(getFunc());
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setStencilReadMask(_readMask);
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setStencilWriteMask(_writeMask);
}

void igStencilFunctionAttr::synchronizeDefault(igVisualContext *vc)
{
    setRefVal(vc->getStencilRefVal());
    setFunc(vc->getStencilFunc());
}

/* Setter for the reflected _func field (the stencil compare function enum). */

void igStencilFunctionAttr::setFunc(IG_GFX_STENCIL_FUNCTION func)
{
    _func = func;
}

/* Setter for the reflected _refVal field (the stencil reference value). */

void igStencilFunctionAttr::setRefVal(unsigned int refVal)
{
    _refVal = refVal;
}
}
}

