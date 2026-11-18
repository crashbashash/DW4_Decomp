void igTextureUnloadAttr_apply(void *arg0, igPsx2VisualContext *arg1) {
    int temp_a2;
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 12));
    if (temp_v1 != 0) {
        temp_a2 = *(int *)((char *)(temp_v1) + 36);
        if (temp_a2 != -1) {
            igPsx2VisualContext_UnloadTexture(arg1, temp_a2);
        }
    }
}

void igTextureUnloadAttr_SynchronizeCachedUnitID(igTextureUnloadAttr *self) {
    self->_cachedUnitID = self->_unitID;
}

void igTextureUnloadAttr_UserPostLoad(igTextureUnloadAttr *self) {
    igAttr_UserPostLoad(self);
    igAttr_SetUnitID((int)self, (short)self->_unitID);
}

void igTextureUnloadAttr_SetUnitID(igTextureUnloadAttr *self, int unitID) {
    self->_unitID = (short)unitID;
    igAttr_SetUnitID((int)self, unitID);
}

void igTextureUnloadAttr_SynchronizeDefault(void) {

}

void igTextureUnloadAttr_GetUnitCount(igTextureUnloadAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

