void Gap__Attrs__igBlendFunctionAttr__vfunc_12(void **arg0) {
    if (igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1) == 0) {
        DAT_0055f4c0[0] = 0;
    }
    Gap__Core__igObject__vfunc_10(arg0);
}

igMetaObject *Gap__Attrs__igBlendFunctionAttr__vfunc_22(void) {
    return g_igBlendFunctionAttr_metaObject[0];
}

/* igBlendEquationExt (DAT_0055f4c0[0]): slot 30 pushes the stored equation to the GS. */
class igBlendEquationExtView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void apply();
};
/* igPsx2VisualContext blend-function setter (igPsx2VisualContext_tail4.inc).
 * matching construct: type sweep — src/dst taken as `long` (64-bit on EE MWCC): the widening keeps
 * each factor in its own register before the context moves into a0, as retail does. */
extern "C" void FUN_00174510(void *context, long src, long dst, unsigned char blendConstant, int blendStage);
extern "C" void FUN_0016e290(igBlendEquationExt *ext, int blendA, int blendB, int blendC, int blendD, char blendConstant);

/* apply: set the blend function on the visual context, then the extended blend equation if present. */
extern "C" void Gap__Attrs__igBlendFunctionAttr__apply(igBlendFunctionAttr *self, void *context) {
    FUN_00174510(context, self->_src, self->_dst, self->_blendConstant, self->_blendStage);
    if (DAT_0055f4c0[0] != 0) {
        ((igBlendEquationExt *)DAT_0055f4c0[0])->_equation = self->_eq;
        FUN_0016e290((igBlendEquationExt *)DAT_0055f4c0[0], self->_blendA, self->_blendB, self->_blendC, self->_blendD,
                     (char)self->_blendConstant);
        ((igBlendEquationExtView *)DAT_0055f4c0[0])->apply();
    }
}

void Gap__Attrs__igBlendFunctionAttr__vfunc_26(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_620_0 *)(arg1))->vX()));
    ((DW4VC_132_1_13c350 *)(arg0))->vX((int)(((DW4VC_628_0 *)(arg1))->vX()));
    if (DAT_0055f4c0[0] == 0) {
        DAT_0055f4c0[0] = ((DW4VC_104_1 *)(arg1))->vX(&text_igBlendEquationExt[0]);
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

