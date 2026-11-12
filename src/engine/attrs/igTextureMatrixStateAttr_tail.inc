void FUN_00141620(void *arg0) {
    *(short *)((char *)(arg0) + 10) = (short) *(int *)((char *)(arg0) + 16);
}

void Gap__Attrs__igTextureMatrixStateAttr__vfunc_24(S_141630 *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_209(arg1, arg0->f16, arg0->b);
}

void Gap__Attrs__igTextureMatrixStateAttr__vfunc_17(void *arg0) {
    FUN_0013b820(arg0);
    FUN_0013b810((int)arg0, *(short *)((char *)(arg0) + 16));
}

void Gap__Attrs__igTextureMatrixStateAttr__vfunc_25(int arg0, int arg1) {
    *(int *)((char *)(arg0) + 16) = (short)arg1;
    FUN_0013b810(arg0, arg1);
}

void Gap__Attrs__igTextureMatrixStateAttr__vfunc_26(void *arg0, void **arg1) {
    ((DW4VC_128_1 *)(((char *)(arg0) + 0)))->vX((int)(((DW4VC_840_1 *)(arg1))->vX((int)(*(int *)((char *)(arg0) + 16)))));
}

/* Setter for the reflected bool field _enabled. */

void Gap__Attrs__igTextureMatrixStateAttr__vfunc_32(igTextureMatrixStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

void Gap__Attrs__igTextureMatrixStateAttr__vfunc_31(igTextureMatrixStateAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

