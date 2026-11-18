void igBlendStateAttr_apply(int arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetBlendingState(arg1, *(unsigned char *)((char *)(arg0) + 12));
}

void igBlendStateAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_612_0 *)(arg1))->vX()));
}

/* Setter: stores the blend-state enable flag (`_enabled`, an igBoolMetaField of the reflected
 * igBlendStateAttr). */
void igBlendStateAttr_SetState(igBlendStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

