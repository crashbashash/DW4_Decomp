void Gap__Attrs__igTextureCoordSourceAttr__vfunc_24(S_140f90* p, int q) { Gap__Gfx__igPsx2VisualContext__vfunc_150(q, p->c, p->a, p->b); }

void Gap__Attrs__igTextureCoordSourceAttr__vfunc_31(igTextureCoordSourceAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

void FUN_00140fd0(void *arg0) {
    *(short *)((char *)(arg0) + 10) = (short) *(int *)((char *)(arg0) + 20);
}

void Gap__Attrs__igTextureCoordSourceAttr__vfunc_17(void *arg0) {
    FUN_0013b820(arg0);
    FUN_0013b810((int)arg0, (short)*(int *)((char *)arg0 + 20));
}

void Gap__Attrs__igTextureCoordSourceAttr__vfunc_25(int arg0, int arg1) {
    *(int *)((char *)(arg0) + 20) = (short)arg1;
    FUN_0013b810(arg0, arg1);
}

void Gap__Attrs__igTextureCoordSourceAttr__vfunc_26(igTextureCoordSourceAttr *self, VisualContextDispatch *context) {
    int mode = self->_mode;
    int texCoordIndex;
    context->getTextureCoordSource(self->_unitID, &mode, &texCoordIndex);
    self->_mode = mode;
    self->_texCoordIndex = texCoordIndex;
}

