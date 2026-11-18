void igStencilFunctionAttr_apply(igStencilFunctionAttr *arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetStencilOps(arg1, arg0->_stenFailOp, arg0->_stenPassZPassOp, arg0->_stenPassZFailOp);
    igPsx2VisualContext_SetStencilRefVal(arg1, arg0->_refVal);
    igPsx2VisualContext_SetStencilFunc(arg1, arg0->_func);
    igPsx2VisualContext_SetStencilReadMask(arg1, arg0->_readMask);
    igPsx2VisualContext_SetStencilWriteMask(arg1, arg0->_writeMask);
}

void igStencilFunctionAttr_SynchronizeDefault(igStencilFunctionAttr *self, igStencilFunctionAttr *source) {
    ((DW4VC_128_1 *)(self))->vX((int)(((DW4VC_648_0 *)(source))->vX()));
    ((DW4VC_136_1 *)(self))->vX((int)(((DW4VC_656_0 *)(source))->vX()));
}

/* Setter for the reflected _func field (the stencil compare function enum). */

void igStencilFunctionAttr_SetFunc(igStencilFunctionAttr *self, int func) {
    self->_func = func;
}

/* Setter for the reflected _refVal field (the stencil reference value). */

void igStencilFunctionAttr_SetRefVal(igStencilFunctionAttr *self, int ref_val) {
    self->_refVal = ref_val;
}

