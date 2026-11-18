void igVertexBlendStateAttr_apply(int arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetVertexBlendingState(arg1, *(bool *)((char *)(arg0) + 12));
}

void igVertexBlendStateAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_848_0 *)(arg1))->vX()));
}

/* Setter for the reflected bool field _enabled. */

void igVertexBlendStateAttr_SetState(igVertexBlendStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

