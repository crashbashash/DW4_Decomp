void Gap__Attrs__igTextureBindAttr__vfunc_31(igTextureBindAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

/* Empty leaf in igTextureBindAttr vtable slot 26 (+0x68): a do-nothing default for a virtual this
 * attribute does not need. */
void Gap__Attrs__igTextureBindAttr__vfunc_26(igTextureBindAttr *self) {
}

void Gap__Attrs__igTextureBindAttr__vfunc_28(igTextureBindAttr *self) {
    void **texture;

    texture = (void **)(self->_texture);
    if (texture != 0) {
        ((BoundTextureVtable *)(texture))->vX();
    }
}

void Gap__Attrs__igTextureBindAttr__vfunc_29(igTextureBindAttr *self) {
    void **texture;

    texture = (void **)(self->_texture);
    if (texture != 0) {
        ((BoundTextureVtable_140d60 *)(texture))->vX();
    }
}

void Gap__Attrs__igTextureBindAttr__vfunc_32(igTextureBindAttr *attr, void *context) {
    igTextureAttr *texture = (igTextureAttr *)attr->_texture;
    Gap__Gfx__igPsx2VisualContext__vfunc_127(context, texture ? texture->_texId : -1, attr->_unitID);
}

void Gap__Attrs__igTextureBindAttr__vfunc_24(igTextureBindAttr *attr, void *context) {
    igTextureAttrView *texture = (igTextureAttrView *)attr->_texture;
    int texId;
    if (texture == 0) {
        Gap__Gfx__igPsx2VisualContext__vfunc_127(context, -1, attr->_unitID);
        return;
    }
    texture->prepare();
    texId = ((igTextureAttr *)attr->_texture)->_texId;
    if (texId >= 0) {
        Gap__Gfx__igPsx2VisualContext__vfunc_127(context, texId, attr->_unitID);
    }
}

void FUN_00140e40(void *arg0) {
    *(short *)((char *)(arg0) + 10) = (short) *(int *)((char *)(arg0) + 16);
}

void Gap__Attrs__igTextureBindAttr__vfunc_17(void *arg0) {
    FUN_0013b820(arg0);
    FUN_0013b810((int)arg0, (short)*(int *)((char *)arg0 + 16));
}

void Gap__Attrs__igTextureBindAttr__vfunc_25(int *arg0, int arg1) {
    arg0[4] = (short)arg1;
    FUN_0013b810((int)arg0, arg1);
}

void FUN_00140e90(int arg0) {
    /* matching construct: cxx_sweep — sp10 and sp0 initialised at their declarations, sp0 declared inside the if */
    V3 sp10 = DAT_00486cb8;
    int var_a1;
    int idx;
    int temp_a4;
    temp_a4 = *(int *)((char *)(g_igTextureBindAttr_metaObject[0]) + 92);
    idx = sp10.b;
    if (GPR_00554b0c == 0) {
        DAT_0055f510[0] = *(int *)(temp_a4 + idx);
        V3 sp0 = DAT_00486cc8;
        DAT_0055f518[0] = *(int *)(temp_a4 + sp0.b);
        GPR_00554b0c = 1;
    }
    if (arg0 != 0) {
        var_a1 = DAT_0055f518[0];
    } else {
        var_a1 = DAT_0055f510[0];
    }
    *(int *)(temp_a4 + idx) = var_a1;
    GPR_00554b08 = arg0;
}

void FUN_00140f40(void) {
    unsigned char sp1F;

    sp1F = 0;
    FUN_00306e50(*(int *)((char *)g_objectSystem[0] + 56), 7, text_enableIgTextureAttrFastApply, &sp1F, 0, 0);
    FUN_00140e90(sp1F);
}

