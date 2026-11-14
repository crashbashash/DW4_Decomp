void FUN_00141250(void *arg0) {
    *(short *)((char *)(arg0) + 10) = (short) *(int *)((char *)(arg0) + 16);
}

void Gap__Attrs__igTextureFunctionAttr__vfunc_25(int arg0, int arg1) {
    *(int *)((char *)(arg0) + 16) = (short)arg1;
    FUN_0013b810(arg0, arg1);
}

void Gap__Attrs__igTextureFunctionAttr__vfunc_17(void *arg0) {
    FUN_0013b820(arg0);
    FUN_0013b810((int)arg0, *(short *)((char *)(arg0) + 16));
}

void FUN_001412a0(void) {
    *(int *)((char *)(DAT_0055ed08[0]) + 52) = (int)(&FUN_00153690);
}

void Gap__Attrs__igTextureFunctionAttr__vfunc_11(void *arg0) {
    igObject_InitDefaults();
    *(int *)((char *)arg0 + 20) = 3;
    *(int *)((char *)arg0 + 24) = 0;
    *(int *)((char *)arg0 + 28) = 2;
    *(int *)((char *)arg0 + 36) = 2;
}

void Gap__Attrs__igTextureFunctionAttr__vfunc_12(void **arg0) {
    if (igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1) == 0) {
        DAT_0055f520[0] = 0;
    }
    igObject_ReleaseDefaults(arg0);
}

igMetaObject *Gap__Attrs__igTextureFunctionAttr__vfunc_22(void) {
    return g_igTextureFunctionAttr_metaObject[0];
}

void Gap__Attrs__igTextureFunctionAttr__vfunc_26(igTextureFunctionAttr *arg0, void **arg1) {
    arg0->_mode = ((DW4VC_596_1 *)(arg1))->vX((int)(arg0->_unitID));
    if (DAT_0055f520[0] == 0) {
        DAT_0055f520[0] = ((DW4VC_104_1 *)(arg1))->vX(&text_igMultiTextureExt[0]);
    }
}

void Gap__Attrs__igTextureFunctionAttr__vfunc_31(igTextureFunctionAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

/* Setter for `_type`; it also clears `_call_state`, the attribute's per-call state byte, so the
 * new type is applied afresh on the next apply. */

void Gap__Attrs__igTextureFunctionAttr__vfunc_32(igTextureFunctionAttr *self, int type) {
    self->_type = type;
    self->_call_state = 0;
}

void Gap__Attrs__igTextureFunctionAttr__vfunc_24(void *arg0x, int arg1) {
    A_141410 *arg0 = (A_141410 *)arg0x;
    int temp_s0;
    if (DAT_0055f520[0] != 0) {
        temp_s0 = arg0->f36;
        if (arg0->f32 == 2) {
            Gap__Gfx__igPsx2VisualContext__vfunc_148(arg1, arg0->f16, arg0->f12);
            return;
        }
        if (arg0->f16 > 0) {
            ((G *)DAT_0055f520[0])->v124(arg0->f16, temp_s0, arg0->f12);
        }
        ((G *)DAT_0055f520[0])->v120(arg0->f16, temp_s0, arg0->f28);
        return;
    }
    Gap__Gfx__igPsx2VisualContext__vfunc_148(arg1, arg0->f16, arg0->f12);
}

