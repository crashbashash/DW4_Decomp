void Gap__Attrs__igBlendFunctionAttr__vfunc_12(void **arg0) {
    if (igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1) == 0) {
        DAT_0055f4c0[0] = 0;
    }
    Gap__Core__igObject__vfunc_10(arg0);
}

igMetaObject *Gap__Attrs__igBlendFunctionAttr__vfunc_22(void) {
    return g_igBlendFunctionAttr_metaObject[0];
}

void Gap__Attrs__igBlendFunctionAttr__vfunc_26(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_620_0 *)(arg1))->vX()));
    ((DW4VC_132_1_13c350 *)(arg0))->vX((int)(((DW4VC_628_0 *)(arg1))->vX()));
    if (DAT_0055f4c0[0] == 0) {
        DAT_0055f4c0[0] = ((DW4VC_104_1 *)(arg1))->vX(&DAT_004d5de0[0]);
    }
}

/* Setter for the destination blend factor (`_dst`, +16); `_src` at +12 is the source factor. */

void Gap__Attrs__igBlendFunctionAttr__vfunc_33(igBlendFunctionAttr *self, int dstFactor) {
    self->_dst = dstFactor;
}

void Gap__Attrs__igBlendFunctionAttr__vfunc_32(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 12) = arg1;
}

void FUN_0013c420(void *arg0) {
    *(short *)((char *)(arg0) + 10) = (short) *(short *)((char *)(arg0) + 30);
}

void Gap__Attrs__igBlendFunctionAttr__vfunc_25(int a0, int a1) {
    *(short *)((char *)a0 + 30) = (short)a1;
    FUN_0013b810(a0, a1);
}

void Gap__Attrs__igBlendFunctionAttr__vfunc_17(void *arg0) {
    FUN_0013b820(arg0);
    FUN_0013b810((int)arg0, *(short *)((char *)(arg0) + 30));
}

void FUN_0013c470(igBlendFunctionAttr *attr)
{
    attr->_blendConstant = (unsigned int)(128.0f * attr->_blendConstantFloat);
}

void Gap__Attrs__igBlendFunctionAttr__vfunc_31(igBlendFunctionAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

