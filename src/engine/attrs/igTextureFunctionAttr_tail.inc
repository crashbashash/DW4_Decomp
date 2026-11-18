int g_igTextureFunctionAttr_multiTextureExt;
void igTextureFunctionAttr_SynchronizeCachedUnitID(igTextureFunctionAttr *self) {
    self->_cachedUnitID = self->_unitID;
}

void igTextureFunctionAttr_SetUnitID(igTextureFunctionAttr *self, int unitID) {
    self->_unitID = (short)unitID;
    igAttr_SetUnitID((int)self, unitID);
}

void igTextureFunctionAttr_UserPostLoad(igTextureFunctionAttr *self) {
    igAttr_UserPostLoad(self);
    igAttr_SetUnitID((int)self, (short)self->_unitID);
}

void FUN_001412a0(void) {
    *(int *)((char *)(DAT_0055ed08[0]) + 52) = (int)(&TEXTURE_FUNCTION_PSX2_GetMetaEnum);
}

void igTextureFunctionAttr_InitDefaults(void *arg0) {
    igObject_InitDefaults((igObject *)arg0);
    *(int *)((char *)arg0 + 20) = 3;
    *(int *)((char *)arg0 + 24) = 0;
    *(int *)((char *)arg0 + 28) = 2;
    *(int *)((char *)arg0 + 36) = 2;
}

void igTextureFunctionAttr_ReleaseDefaults(void **arg0) {
    if (igMetaObject_CountInstances((igMetaObject *)(((DW4VC_88_0 *)(arg0))->vX()), 1) == 0) {
        g_igTextureFunctionAttr_multiTextureExt = 0;
    }
    igObject_ReleaseDefaults((igObject *)arg0);
}

igMetaObject *igTextureFunctionAttr_GetMeta(void) {
    return g_igTextureFunctionAttr_metaObject;
}

void igTextureFunctionAttr_SynchronizeDefault(igTextureFunctionAttr *arg0, void **arg1) {
    arg0->_mode = ((DW4VC_596_1 *)(arg1))->vX((int)(arg0->_unitID));
    if (g_igTextureFunctionAttr_multiTextureExt == 0) {
        g_igTextureFunctionAttr_multiTextureExt = ((DW4VC_104_1 *)(arg1))->vX("igMultiTextureExt");
    }
}

void igTextureFunctionAttr_GetUnitCount(igTextureFunctionAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

/* Setter for `_type`; it also clears `_call_state`, the attribute's per-call state byte, so the
 * new type is applied afresh on the next apply. */

void igTextureFunctionAttr_SetType(igTextureFunctionAttr *self, int type) {
    self->_type = type;
    self->_call_state = 0;
}

void igTextureFunctionAttr_apply(void *arg0x, igPsx2VisualContext *arg1) {
    A_141410 *arg0 = (A_141410 *)arg0x;
    int temp_s0;
    if (g_igTextureFunctionAttr_multiTextureExt != 0) {
        temp_s0 = arg0->f36;
        if (arg0->f32 == 2) {
            igPsx2VisualContext_SetTextureStageFunc(arg1, arg0->f16, arg0->f12);
            return;
        }
        if (arg0->f16 > 0) {
            ((G *)g_igTextureFunctionAttr_multiTextureExt)->v124(arg0->f16, temp_s0, arg0->f12);
        }
        ((G *)g_igTextureFunctionAttr_multiTextureExt)->v120(arg0->f16, temp_s0, arg0->f28);
        return;
    }
    igPsx2VisualContext_SetTextureStageFunc(arg1, arg0->f16, arg0->f12);
}

