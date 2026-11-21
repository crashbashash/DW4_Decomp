namespace Gap {
namespace Attrs {

void igStencilFunctionAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetStencilOps((igPsx2VisualContext *)vc, _stenFailOp, _stenPassZPassOp, _stenPassZFailOp);
    igPsx2VisualContext_SetStencilRefVal((igPsx2VisualContext *)vc, _refVal);
    igPsx2VisualContext_SetStencilFunc((igPsx2VisualContext *)vc, getFunc());
    igPsx2VisualContext_SetStencilReadMask((igPsx2VisualContext *)vc, _readMask);
    igPsx2VisualContext_SetStencilWriteMask((igPsx2VisualContext *)vc, _writeMask);
}

void igStencilFunctionAttr::synchronizeDefault(igVisualContext *vc)
{
    setRefVal(((igVisualContextDispatchView *)vc)->getStencilRefVal());
    setFunc(((igVisualContextDispatchView *)vc)->getStencilFunc());
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

