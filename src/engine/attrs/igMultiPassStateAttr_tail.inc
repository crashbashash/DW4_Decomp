void Gap__Attrs__igMultiPassStateAttr__vfunc_24(int arg0, int arg1) {
    FUN_001757c0(arg1, *(int *)((char *)(arg0) + 12));
}

void Gap__Attrs__igMultiPassStateAttr__vfunc_26(igMultiPassStateAttrView *self, igPsx2VisualContextView *context)
{
    self->vfunc_30(context->_bMultiPassNum);
}

/* Setter for the pass count (`_numPasses`, +12). */

void Gap__Attrs__igMultiPassStateAttr__vfunc_32(igMultiPassStateAttr *self, int numPasses) {
    self->_numPasses = numPasses;
}

