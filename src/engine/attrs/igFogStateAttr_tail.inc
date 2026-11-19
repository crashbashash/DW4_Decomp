void igFogStateAttr_apply(igFogStateAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetFogState(arg1, *(bool *)&self->_enabled);
}

void igFogStateAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_968_0 *)(arg1))->vX()));
}

void igFogStateAttr_SetState(igFogStateAttr *self, char arg1) {
    self->_enabled = arg1;
}

