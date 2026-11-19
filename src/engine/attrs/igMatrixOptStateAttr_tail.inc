void igMatrixOptStateAttr_apply(igMatrixOptStateAttr *self, int arg1) {
    igPsx2VisualContext_SetMatrixOptimizationState((igPsx2VisualContext *)arg1, self->_enabled);
}

void igMatrixOptStateAttr_SynchronizeDefault(igMatrixOptStateAttrView *self, igPsx2VisualContext *context) {
    self->setState(igPsx2VisualContext_GetMatrixOptimizationState(context));
}

/* Setter for the attribute's reflected _enabled flag. */
void igMatrixOptStateAttr_SetState(igMatrixOptStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

