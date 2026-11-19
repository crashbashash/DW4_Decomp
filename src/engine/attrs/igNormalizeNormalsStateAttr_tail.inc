void igNormalizeNormalsStateAttr_apply(igNormalizeNormalsStateAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetNormalizeNormalsState(arg1, self->_enabled);
}

void igNormalizeNormalsStateAttr_SynchronizeDefault(igNormalizeNormalsStateAttr *self, void **arg1) {
    self->_enabled = ((DW4VC_456_0 *)(arg1))->vX();
}

