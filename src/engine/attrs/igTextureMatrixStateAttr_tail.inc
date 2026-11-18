void igTextureMatrixStateAttr_SynchronizeCachedUnitID(igTextureMatrixStateAttr *self) {
    self->_cachedUnitID = self->_unitID;
}

void igTextureMatrixStateAttr_apply(S_141630 *arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetTextureMatrixState(arg1, arg0->f16, arg0->b);
}

void igTextureMatrixStateAttr_UserPostLoad(igTextureMatrixStateAttr *self) {
    igAttr_UserPostLoad(self);
    igAttr_SetUnitID((int)self, (short)self->_unitID);
}

void igTextureMatrixStateAttr_SetUnitID(igTextureMatrixStateAttr *self, int unitID) {
    self->_unitID = (short)unitID;
    igAttr_SetUnitID((int)self, unitID);
}

void igTextureMatrixStateAttr_SynchronizeDefault(void *arg0, void **arg1) {
    ((DW4VC_128_1 *)(((char *)(arg0) + 0)))->vX((int)(((DW4VC_840_1 *)(arg1))->vX((int)(*(int *)((char *)(arg0) + 16)))));
}

/* Setter for the reflected bool field _enabled. */

void igTextureMatrixStateAttr_SetState(igTextureMatrixStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

void igTextureMatrixStateAttr_GetUnitCount(igTextureMatrixStateAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

