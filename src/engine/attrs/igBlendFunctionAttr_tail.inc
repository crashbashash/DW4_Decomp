int g_igBlendFunctionAttr_blendEquationExt;
void igBlendFunctionAttr_ReleaseDefaults(void **arg0) {
    if (igMetaObject_CountInstances((igMetaObject *)(((DW4VC_88_0 *)(arg0))->vX()), 1) == 0) {
        g_igBlendFunctionAttr_blendEquationExt = 0;
    }
    igObject_ReleaseDefaults((igObject *)arg0);
}

igMetaObject *igBlendFunctionAttr_GetMeta(void) {
    return g_igBlendFunctionAttr_metaObject;
}

/* igBlendEquationExt (g_igBlendFunctionAttr_blendEquationExt): slot 30 pushes the stored equation to the GS. */
class igBlendEquationExtView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void apply();
};

/* apply: set the blend function on the visual context, then the extended blend equation if present. */
extern "C" void Gap__Attrs__igBlendFunctionAttr__apply(igBlendFunctionAttr *self, igPsx2VisualContext *context) {
    FUN_00174510(context, (IG_GFX_BLENDING_FUNCTION)self->_src, (IG_GFX_BLENDING_FUNCTION)self->_dst, self->_blendConstant, self->_blendStage);
    if (g_igBlendFunctionAttr_blendEquationExt != 0) {
        ((igBlendEquationExt *)g_igBlendFunctionAttr_blendEquationExt)->_equation = self->_eq;
        igPsx2BlendEquationExt_SetBlendFactors((igPsx2BlendEquationExt *)g_igBlendFunctionAttr_blendEquationExt, self->_blendA, self->_blendB, self->_blendC, self->_blendD,
                     (char)self->_blendConstant);
        ((igBlendEquationExtView *)g_igBlendFunctionAttr_blendEquationExt)->apply();
    }
}

void igBlendFunctionAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_620_0 *)(arg1))->vX()));
    ((DW4VC_132_1_13c350 *)(arg0))->vX((int)(((DW4VC_628_0 *)(arg1))->vX()));
    if (g_igBlendFunctionAttr_blendEquationExt == 0) {
        g_igBlendFunctionAttr_blendEquationExt = ((DW4VC_104_1 *)(arg1))->vX("igBlendEquationExt");
    }
}

/* Setter for the destination blend factor (`_dst`, +16); `_src` at +12 is the source factor. */

void igBlendFunctionAttr_SetDestination(igBlendFunctionAttr *self, int dstFactor) {
    self->_dst = dstFactor;
}

void igBlendFunctionAttr_SetSource(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 12) = arg1;
}

void igBlendFunctionAttr_SynchronizeCachedUnitID(igBlendFunctionAttr *self) {
    self->_cachedUnitID = self->_blendStage;
}

void igBlendFunctionAttr_SetUnitID(igBlendFunctionAttr *self, int unitID) {
    self->_blendStage = (short)unitID;
    igAttr_SetUnitID((int)self, unitID);
}

void igBlendFunctionAttr_UserPostLoad(igBlendFunctionAttr *self) {
    igAttr_UserPostLoad(self);
    igAttr_SetUnitID((int)self, (short)self->_blendStage);
}

void igBlendFunctionAttr_SynchronizeBlendConstant(igBlendFunctionAttr *attr)
{
    attr->_blendConstant = (unsigned int)(128.0f * attr->_blendConstantFloat);
}

void igBlendFunctionAttr_GetUnitCount(igBlendFunctionAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

