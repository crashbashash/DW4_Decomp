void igTexGenMatrixAttr_SynchronizeCachedUnitID(igTexGenMatrixAttr *self) {
    self->_cachedUnitID = self->_unitID;
}

void igTexGenMatrixAttr_SetUnitID(igTexGenMatrixAttr *self, int unitID) {
    self->_unitID = (short)unitID;
    igAttr_SetUnitID((int)self, unitID);
}

void igTexGenMatrixAttr_UserPostLoad(igTexGenMatrixAttr *self) {
    igAttr_UserPostLoad(self);
    igAttr_SetUnitID((int)self, (short)self->_unitID);
}

void igTexGenMatrixAttr_apply(char * arg0, int arg1) {
    FUN_00173ed0(arg1, 14, (arg0 + 12));
}

void igTexGenMatrixAttr_SynchronizeDefault(igTexGenMatrixAttr *self, void *context)
{
    float m[16];

    igMatrix44f_SetIdentity(m);
    FUN_00173fd0(context, 14, m);
    igMatrix44f_Copy(self->m, m);
}

