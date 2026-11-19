void igTextureMatrixAttr_apply(igTextureMatrixAttr *self, igPsx2VisualContext *context) {
    igPsx2VisualContext_SetTextureMatrixProjectiveState(context, self->_unitID, self->_isProjective);
    igPsx2VisualContext_SetMatrix(context, self->_unitID + 2, (char *)self->_m);
}

void igTextureMatrixAttr_SynchronizeCachedUnitID(igTextureMatrixAttr *self) {
    self->_cachedUnitID = self->_unitID;
}

void igTextureMatrixAttr_UserPostLoad(igTextureMatrixAttr *self) {
    igAttr_UserPostLoad(self);
    igAttr_SetUnitID((int)self, (short)self->_unitID);
}

void igTextureMatrixAttr_SetUnitID(igTextureMatrixAttr *self, int unitID) {
    self->_unitID = (short)unitID;
    igAttr_SetUnitID((int)self, unitID);
}

void igTextureMatrixAttr_SynchronizeDefault(igTextureMatrixAttr *self, igObject *context)
{
    float m[16];

    igMatrix44f_SetIdentity(m);
    ((VisualContextMatrixSlots *)context)->getMatrix(self->_unitID + 2, m);
    ((MatrixAttrSlots *)self)->setMatrix(m);
    self->_isProjective = igPsx2VisualContext_GetTextureMatrixProjectiveState((igPsx2VisualContext *)context, self->_unitID);
}

void igTextureMatrixAttr_SetMatrix(igTextureMatrixAttr *self, const float *matrix) {
    igMatrix44f_Copy(self->_m, matrix);
}

void igTextureMatrixAttr_GetUnitCount(igTextureMatrixAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

