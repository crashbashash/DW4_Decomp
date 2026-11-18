void igClippingStateAttr_apply(int arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetViewportClippingState(arg1, *(unsigned char *)((char *)(arg0) + 12));
}

void igClippingStateAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_896_0 *)(arg1))->vX()));
}

/* Setter: stores the clipping-state enable flag (`_enabled`, an igBoolMetaField of the reflected
 * igClippingStateAttr). */
void igClippingStateAttr_SetState(igClippingStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

