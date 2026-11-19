void igStencilStateAttr_apply(igStencilStateAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetStencilState(arg1, *(bool *)&self->_enabled);
}

void igStencilStateAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_640_0 *)(arg1))->vX()));
}

void igStencilStateAttr_SetState(igStencilStateAttr *self, char arg1) {
    self->_enabled = arg1;
}

