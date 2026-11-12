void Gap__Attrs__igStencilFunctionAttr__vfunc_24(igStencilFunctionAttr *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_165(arg1, arg0->_stenFailOp, arg0->_stenPassZPassOp, arg0->_stenPassZFailOp);
    Gap__Gfx__igPsx2VisualContext__vfunc_161(arg1, arg0->_refVal);
    Gap__Gfx__igPsx2VisualContext__vfunc_163(arg1, arg0->_func);
    Gap__Gfx__igPsx2VisualContext__vfunc_167(arg1, arg0->_readMask);
    Gap__Gfx__igPsx2VisualContext__vfunc_169(arg1, arg0->_writeMask);
}

void Gap__Attrs__igStencilFunctionAttr__vfunc_26(igStencilFunctionAttr *self, igStencilFunctionAttr *source) {
    ((DW4VC_128_1 *)(self))->vX((int)(((DW4VC_648_0 *)(source))->vX()));
    ((DW4VC_136_1 *)(self))->vX((int)(((DW4VC_656_0 *)(source))->vX()));
}

/* Setter for the reflected _func field (the stencil compare function enum). */

void Gap__Attrs__igStencilFunctionAttr__vfunc_34(igStencilFunctionAttr *self, int func) {
    self->_func = func;
}

/* Setter for the reflected _refVal field (the stencil reference value). */

void Gap__Attrs__igStencilFunctionAttr__vfunc_32(igStencilFunctionAttr *self, int ref_val) {
    self->_refVal = ref_val;
}

