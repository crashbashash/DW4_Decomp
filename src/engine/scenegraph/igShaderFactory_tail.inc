int Gap__Sg__igShaderFactory__vfunc_23(void *dummy, VA_1d8980 *arg1, void *, int) {
    VO_1d8980 *shader = ((P_1d8980 *)arg1)->f36;
    igSmartPointer<Attr> attr(((Attr *)FUN_0013aec0(igObject_GetAllocator())));
    shader->v100();
    shader->v96(attr.get(), attr.get(), 0);
    arg1->v124();
    return 1;
}

void Gap__Sg__igShaderFactory__vfunc_24(void **arg0) {
    void *temp_a0;

    *arg0 = 0;
    temp_a0 = *arg0;
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) + 4) = (int) (*(int *)((char *)(temp_a0) + 4) + 1);
    }
}

void Gap__Sg__igShaderFactory__vfunc_25(T_1d8a60 *arg0, int arg1) {
    if (arg1 != arg0->f20) {
        arg0->f20 = arg1;
        if (arg0->f20 == 0) {
            ((V_1d8a60 *)arg0)->vX();
        }
    }
}

void Gap__Sg__igShaderFactory__vfunc_26(void) {

}

