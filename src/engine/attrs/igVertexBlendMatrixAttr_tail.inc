void igVertexBlendMatrixAttr_apply(igVertexBlendMatrixAttr *self, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetMatrix(arg1, self->_blendMatID + 10, (char *)self + 0xC);
}

void igVertexBlendMatrixAttr_SynchronizeCachedUnitID(igVertexBlendMatrixAttr *self) {
    self->_cachedUnitID = self->_blendMatID;
}

void igVertexBlendMatrixAttr_SetUnitID(igVertexBlendMatrixAttr *self, int unitID) {
    self->_blendMatID = (short)unitID;
    igAttr_SetUnitID((int)self, unitID);
}

void igVertexBlendMatrixAttr_UserPostLoad(igVertexBlendMatrixAttr *self) {
    igAttr_UserPostLoad(self);
    igAttr_SetUnitID((int)self, (short)self->_blendMatID);
}

void igVertexBlendMatrixAttr_SynchronizeDefault(igVertexBlendMatrixAttr *self, void **arg1) {
    int sp30[16];

    igMatrix44f_SetIdentity((float *)sp30);
    ((V832 *)arg1)->vX(self->_blendMatID + 0xA, sp30);
    ((V128 *)self)->vX(sp30);
}

void igVertexBlendMatrixAttr_SetMatrix(igVertexBlendMatrixAttr *self, const float *matrix) {
    igMatrix44f_Copy(self->_m, matrix);
}

void igVertexBlendMatrixAttr_GetUnitCount(igVertexBlendMatrixAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(13);
}

static inline bool InRange(float x, float lo, float hi) {
    return x >= lo && x <= hi;
}

