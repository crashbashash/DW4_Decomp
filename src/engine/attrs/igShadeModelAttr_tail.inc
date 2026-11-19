void igShadeModelAttr_apply(igShadeModelAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetShadingMode(arg1, (unsigned int)self->_mode);
}

void igShadeModelAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_912_0 *)(arg1))->vX()));
}

/* Setter for the reflected _mode field (the shading mode enum). */

void igShadeModelAttr_SetMode(igShadeModelAttr *self, int mode) {
    self->_mode = mode;
}

void FUN_00140360(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 36) = arg1;
}

