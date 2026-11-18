void igTextureCoordSourceAttr_apply(S_140f90* p, igPsx2VisualContext *q) { igPsx2VisualContext_SetTextureStageCoordSource(q, p->c, p->a, p->b); }

void igTextureCoordSourceAttr_GetUnitCount(igTextureCoordSourceAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

void igTextureCoordSourceAttr_SynchronizeCachedUnitID(igTextureCoordSourceAttr *self) {
    self->_cachedUnitID = self->_unitID;
}

void igTextureCoordSourceAttr_UserPostLoad(igTextureCoordSourceAttr *self) {
    igAttr_UserPostLoad(self);
    igAttr_SetUnitID((int)self, (short)self->_unitID);
}

void igTextureCoordSourceAttr_SetUnitID(igTextureCoordSourceAttr *self, int unitID) {
    self->_unitID = (short)unitID;
    igAttr_SetUnitID((int)self, unitID);
}

void igTextureCoordSourceAttr_SynchronizeDefault(igTextureCoordSourceAttr *self, VisualContextDispatch *context) {
    int mode = self->_mode;
    int texCoordIndex;
    context->getTextureCoordSource(self->_unitID, &mode, &texCoordIndex);
    self->_mode = mode;
    self->_texCoordIndex = texCoordIndex;
}

