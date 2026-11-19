void igDepthWriteStateAttr_apply(igDepthWriteStateAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetDepthWriteState(arg1, self->_enabled);
}

void igDepthWriteStateAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_952_0 *)(arg1))->vX()));
}

/* Setter for the attribute's reflected _enabled flag. */
void igDepthWriteStateAttr_SetState(igDepthWriteStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

