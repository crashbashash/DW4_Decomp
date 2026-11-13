void Gap__Attrs__igVertexBlendMatrixAttr__vfunc_24(void *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_203(arg1, *(unsigned short *)((char *)arg0 + 76) + 10, (char *)arg0 + 0xC);
}

void FUN_00141900(void *arg0) {
    *(unsigned short *)((char *)(arg0) + 10) = (unsigned short) *(unsigned short *)((char *)(arg0) + 76);
}

void Gap__Attrs__igVertexBlendMatrixAttr__vfunc_25(int a0, int a1) {
    *(short *)((char *)a0 + 76) = (short)a1;
    FUN_0013b810(a0, a1);
}

void Gap__Attrs__igVertexBlendMatrixAttr__vfunc_17(void *arg0) {
    FUN_0013b820(arg0);
    FUN_0013b810((int)arg0, *(short *)((char *)(arg0) + 76));
}

void Gap__Attrs__igVertexBlendMatrixAttr__vfunc_26(void *arg0, void **arg1) {
    int sp30[16];

    igMatrix44f_SetIdentity(sp30);
    ((V832 *)arg1)->vX(*(unsigned short *)((char *)(arg0) + 76) + 0xA, sp30);
    ((V128 *)arg0)->vX(sp30);
}

void Gap__Attrs__igVertexBlendMatrixAttr__vfunc_32(int a0) {
    igMatrix44f_Copy((char *)a0 + 12);
}

void Gap__Attrs__igVertexBlendMatrixAttr__vfunc_31(igVertexBlendMatrixAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(13);
}

static inline bool InRange(float x, float lo, float hi) {
    return x >= lo && x <= hi;
}

