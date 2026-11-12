int Gap__Attrs__igStencilFunctionAttr__vfunc_22(void) {
    return DAT_0055ee50[0];
}

/* Accessor: returns the stencil reference value (`_refVal`, igUnsignedIntMetaField, +12). */
int Gap__Attrs__igStencilFunctionAttr__vfunc_33(igStencilFunctionAttr *self) {
    return self->_refVal;
}

/* Setter for the three stencil operations (the `_stenFailOp`, `_stenPassZPassOp` and
 * `_stenPassZFailOp` enum fields). Getter counterpart: vfunc_36. */

void Gap__Attrs__igStencilFunctionAttr__vfunc_35(igStencilFunctionAttr *self, int failOp, int passZPassOp, int passZFailOp) {
    self->_stenFailOp = failOp;
    self->_stenPassZPassOp = passZPassOp;
    self->_stenPassZFailOp = passZFailOp;
}

/* Getter for the three stencil operations (the `_stenFailOp`, `_stenPassZPassOp` and
 * `_stenPassZFailOp` enum fields), written through the output pointers. Setter counterpart:
 * vfunc_35. */

void Gap__Attrs__igStencilFunctionAttr__vfunc_36(igStencilFunctionAttr *self, int *outFailOp, int *outPassZPassOp, int *outPassZFailOp) {
    *outFailOp = self->_stenFailOp;
    *outPassZPassOp = self->_stenPassZPassOp;
    *outPassZFailOp = self->_stenPassZFailOp;
}

/* Setter for the reflected _readMask field (the stencil compare mask). */

void Gap__Attrs__igStencilFunctionAttr__vfunc_37(igStencilFunctionAttr *self, int read_mask) {
    self->_readMask = read_mask;
}

/* Setter for the `_writeMask` field. vfunc_37 sets `_readMask`, vfunc_32 `_refVal`. */

void Gap__Attrs__igStencilFunctionAttr__vfunc_38(igStencilFunctionAttr *self, int writeMask) {
    self->_writeMask = writeMask;
}

