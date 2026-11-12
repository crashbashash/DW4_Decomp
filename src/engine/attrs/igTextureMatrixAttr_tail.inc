void Gap__Attrs__igTextureMatrixAttr__vfunc_24(S_1414d0 *p, int q) { FUN_0017c710(q, p->a, p->b); Gap__Gfx__igPsx2VisualContext__vfunc_203(q, p->a + 2, (char *)p + 12); }

void FUN_00141520(void *arg0) {
    *(short *)((char *)(arg0) + 10) = (short) *(int *)((char *)(arg0) + 76);
}

void Gap__Attrs__igTextureMatrixAttr__vfunc_17(void *arg0) {
    FUN_0013b820(arg0);
    FUN_0013b810((int)arg0, (short)*(int *)((char *)arg0 + 76));
}

void Gap__Attrs__igTextureMatrixAttr__vfunc_25(int arg0, int arg1) {
    *(int *)((char *)(arg0) + 76) = (short)arg1;
    FUN_0013b810(arg0, arg1);
}

void Gap__Attrs__igTextureMatrixAttr__vfunc_26(igTextureMatrixAttr *self, igObject *context)
{
    float m[16];

    igMatrix44f_SetIdentity(m);
    ((VisualContextMatrixSlots *)context)->getMatrix(self->_unitID + 2, m);
    ((MatrixAttrSlots *)self)->setMatrix(m);
    self->_isProjective = FUN_0017c790(context, self->_unitID);
}

void Gap__Attrs__igTextureMatrixAttr__vfunc_32(int a0) {
    Matrix44_Copy((char *)a0 + 12);
}

void Gap__Attrs__igTextureMatrixAttr__vfunc_31(igTextureMatrixAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

