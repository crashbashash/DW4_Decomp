void igMatrixOptStateAttr_apply(int arg0, int arg1) {
    igPsx2VisualContext_SetMatrixOptimizationState((igPsx2VisualContext *)arg1, *(unsigned char *)((char *)(arg0) + 12));
}

void igMatrixOptStateAttr_SynchronizeDefault(igMatrixOptStateAttrView *self, igPsx2VisualContext *context) {
    self->setState(igPsx2VisualContext_GetMatrixOptimizationState(context));
}

/* Setter for the attribute's reflected _enabled flag. */
void igMatrixOptStateAttr_SetState(igMatrixOptStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

