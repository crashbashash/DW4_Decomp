void igMultiPassStateAttr_apply(igMultiPassStateAttr *self, int arg1) {
    FUN_001757c0((igPsx2VisualContext *)arg1, self->_numPasses);
}

void igMultiPassStateAttr_SynchronizeDefault(igMultiPassStateAttrView *self, igPsx2VisualContextView *context)
{
    self->vfunc_30(context->_bMultiPassNum);
}

/* Setter for the pass count (`_numPasses`, +12). */

void igMultiPassStateAttr_SetNumPasses(igMultiPassStateAttr *self, int numPasses) {
    self->_numPasses = numPasses;
}

