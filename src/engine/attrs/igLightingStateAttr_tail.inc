void igLightingStateAttr_apply(igLightingStateAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetLightingState(arg1, self->_enabled);
}

void igLightingStateAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_304_0 *)(arg1))->vX()));
}

/* Setter for the attribute's reflected _enabled flag; lighting off means unlit geometry. */
void igLightingStateAttr_SetState(igLightingStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

