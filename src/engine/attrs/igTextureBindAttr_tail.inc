int g_igTextureBindAttr_applySlotFast;
int g_igTextureBindAttr_applySlotDefault;
void igTextureBindAttr_GetUnitCount(igTextureBindAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

/* Empty leaf in igTextureBindAttr vtable slot 26 (+0x68): a do-nothing default for a virtual this
 * attribute does not need. */
void igTextureBindAttr_SynchronizeDefault(igTextureBindAttr *self) {
}

void igTextureBindAttr_Reset(igTextureBindAttr *self) {
    void **texture;

    texture = (void **)(self->_texture);
    if (texture != 0) {
        ((BoundTextureVtable *)(texture))->vX();
    }
}

void igTextureBindAttr_Setup(igTextureBindAttr *self) {
    void **texture;

    texture = (void **)(self->_texture);
    if (texture != 0) {
        ((BoundTextureVtable_140d60 *)(texture))->vX();
    }
}

void Gap__Attrs__igTextureBindAttr__vfunc_32(igTextureBindAttr *attr, igPsx2VisualContext *context) {
    igTextureAttr *texture = (igTextureAttr *)attr->_texture;
    igPsx2VisualContext_SetTexture(context, texture ? texture->_texId : -1, attr->_unitID);
}

void igTextureBindAttr_apply(igTextureBindAttr *attr, igPsx2VisualContext *context) {
    igTextureAttrView *texture = (igTextureAttrView *)attr->_texture;
    int texId;
    if (texture == 0) {
        igPsx2VisualContext_SetTexture(context, -1, attr->_unitID);
        return;
    }
    texture->prepare();
    texId = ((igTextureAttr *)attr->_texture)->_texId;
    if (texId >= 0) {
        igPsx2VisualContext_SetTexture(context, texId, attr->_unitID);
    }
}

void igTextureBindAttr_SynchronizeCachedUnitID(igTextureBindAttr *self) {
    self->_cachedUnitID = self->_unitID;
}

void igTextureBindAttr_UserPostLoad(igTextureBindAttr *self) {
    igAttr_UserPostLoad(self);
    igAttr_SetUnitID((int)self, (short)self->_unitID);
}

void igTextureBindAttr_SetUnitID(igTextureBindAttr *self, int unitID) {
    self->_unitID = (short)unitID;
    igAttr_SetUnitID((int)self, unitID);
}

void igTextureBindAttr_SetFastApply(int arg0) {
    /* matching construct: cxx_sweep — sp10 and sp0 initialised at their declarations, sp0 declared inside the if */
    V3 sp10 = { 0, 0x60, 0.0f };
    int var_a1;
    int idx;
    int temp_a4;
    temp_a4 = *(int *)((char *)(g_igTextureBindAttr_metaObject) + 92);
    idx = sp10.b;
    if (g_igTextureBindAttr_slotsCached == 0) {
        g_igTextureBindAttr_applySlotDefault = *(int *)(temp_a4 + idx);
        V3 sp0 = { 0, 0x80, 0.0f };
        g_igTextureBindAttr_applySlotFast = *(int *)(temp_a4 + sp0.b);
        g_igTextureBindAttr_slotsCached = 1;
    }
    if (arg0 != 0) {
        var_a1 = g_igTextureBindAttr_applySlotFast;
    } else {
        var_a1 = g_igTextureBindAttr_applySlotDefault;
    }
    *(int *)(temp_a4 + idx) = var_a1;
    g_igTextureBindAttr_fastApplyEnabled = arg0;
}

void igTextureBindAttr_ConfigureFastApply(void) {
    unsigned char sp1F;

    sp1F = 0;
    igRegistry_GetValueBool((igRegistry *)(*(int *)((char *)g_objectSystem + 56)), 7, "enableIgTextureAttrFastApply", (unsigned char *)&sp1F, 0, 0);
    igTextureBindAttr_SetFastApply(sp1F);
}

