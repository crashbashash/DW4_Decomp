void igPolygonModeAttr_apply(int arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetRenderMode(arg1, (unsigned int)*(int *)((char *)(arg0) + 12));
}

void igPolygonModeAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_960_0 *)(arg1))->vX()));
}

/* Setter for the attribute's reflected _mode enum field (+0x0c); stores the value as given without
 * validation. */

void igPolygonModeAttr_SetMode(igPolygonModeAttr *self, int mode) {
    self->_mode = mode;
}

