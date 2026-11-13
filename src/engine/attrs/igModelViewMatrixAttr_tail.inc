void Gap__Attrs__igModelViewMatrixAttr__vfunc_24(char * arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_203(arg1, 1, (arg0 + 12));
}

void FUN_0013f670(void) {

}

igModelViewMatrixAttr *FUN_0013f680(void) {
    int allocator;
    if (g_igModelViewMatrixAttr_instance == 0) {
        if (g_useOwnerAllocator != 0) { int owner = Memory_GetAllocatorBySelector(DAT_00587028[0]); allocator = owner; } else { int fallback = Memory_GetAllocatorBySelector(DAT_005870f8[0]); allocator = fallback; }
        g_igModelViewMatrixAttr_instance.release();
        g_igModelViewMatrixAttr_instance.p = (igModelViewMatrixAttr *)FUN_001356b0(allocator);
    }
    return g_igModelViewMatrixAttr_instance;
}

void FUN_0013f730(void) {
    g_igModelViewMatrixAttr_instance.clear();
}

void Gap__Attrs__igModelViewMatrixAttr__vfunc_26(void *arg0, void *arg1) {
    float m[16];
    igMatrix44f_SetIdentity(m);
    ((VA *)arg1)->vX(1, m);
    ((VB_13f790 *)arg0)->vY(m);
}

void Gap__Attrs__igModelViewMatrixAttr__vfunc_32(int a0) {
    Matrix44_Copy((char *)a0 + 12);
}

void FUN_0013f800(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 20) = arg1;
}

