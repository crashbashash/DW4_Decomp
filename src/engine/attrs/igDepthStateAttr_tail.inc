void igDepthStateAttr_SynchronizeDefault(void **self, void **source) {
    ((DW4VC_128_1 *)(self))->vX((int)(((DW4VC_936_0 *)(source))->vX()));
}

/* Setter for the attribute's reflected _enabled flag. */
void igDepthStateAttr_SetState(igDepthStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

void igDepthStateAttr_apply(igDepthStateAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetDepthTestState(arg1, *(bool *)&self->_enabled);
}

