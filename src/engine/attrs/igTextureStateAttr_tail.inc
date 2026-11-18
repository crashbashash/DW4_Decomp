void igTextureStateAttr_SynchronizeCachedUnitID(igTextureStateAttr *self) {
    self->_cachedUnitID = self->_unitID;
}

void igTextureStateAttr_apply(igTextureStateAttr *self, igPsx2VisualContext *context) {
    /* reflected.h spells the igBool _enabled as unsigned char; the setter takes the kit's igBool (bool). */
    igPsx2VisualContext_SetTextureStageState(context, self->_unitID, *(bool *)&self->_enabled);
}

void igTextureStateAttr_UserPostLoad(igTextureStateAttr *self) {
    igAttr_UserPostLoad(self);
    igAttr_SetUnitID((int)self, (short)self->_unitID);
}

void igTextureStateAttr_SetUnitID(igTextureStateAttr *self, int unitID) {
    self->_unitID = (short)unitID;
    igAttr_SetUnitID((int)self, unitID);
}

void igTextureStateAttr_SynchronizeDefault(void *arg0, void **arg1) {
    ((DW4VC_128_1 *)(((char *)(arg0) + 0)))->vX((int)(((DW4VC_472_1 *)(arg1))->vX((int)(*(int *)((char *)(arg0) + 16)))));
}

/* Setter for the reflected bool field _enabled. */

void igTextureStateAttr_SetState(igTextureStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

void igTextureStateAttr_GetUnitCount(igTextureStateAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

