void igModelViewMatrixAttr_apply(char * arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetMatrix(arg1, 1, (char *)(arg0 + 12));
}

void FUN_0013f670(void) {

}

igModelViewMatrixAttr *FUN_0013f680(void) {
    int allocator;
    if (g_igModelViewMatrixAttr_instance == 0) {
        if (g_useOwnerAllocator != 0) { int owner = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent); allocator = owner; } else { int fallback = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleAttribute); allocator = fallback; }
        g_igModelViewMatrixAttr_instance.release();
        g_igModelViewMatrixAttr_instance.p = (igModelViewMatrixAttr *)igModelViewMatrixAttr_CreateInstance(allocator);
    }
    return g_igModelViewMatrixAttr_instance;
}

void igModelViewMatrixAttr_UserUnregister(void) {
    g_igModelViewMatrixAttr_instance.clear();
}

void igModelViewMatrixAttr_SynchronizeDefault(void *arg0, void *arg1) {
    float m[16];
    igMatrix44f_SetIdentity(m);
    ((VA *)arg1)->vX(1, m);
    ((VB_13f790 *)arg0)->vY(m);
}

void igModelViewMatrixAttr_SetMatrix(igModelViewMatrixAttr *self, const float *matrix) {
    igMatrix44f_Copy(self->_m, matrix);
}

void FUN_0013f800(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 20) = arg1;
}

