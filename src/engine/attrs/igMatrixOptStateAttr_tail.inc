void igMatrixOptStateAttr_apply(int arg0, int arg1) {
    FUN_00174850(arg1, *(unsigned char *)((char *)(arg0) + 12));
}

void igMatrixOptStateAttr_SynchronizeDefault(void **arg0, int arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(FUN_001748c0(arg1)));
}

/* Setter for the attribute's reflected _enabled flag. */
void igMatrixOptStateAttr_SetState(igMatrixOptStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

