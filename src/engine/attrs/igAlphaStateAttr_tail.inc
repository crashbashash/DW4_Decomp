void Gap__Attrs__igAlphaStateAttr__vfunc_24(int arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_217(arg1, *(unsigned char *)((char *)(arg0) + 12));
}

void Gap__Attrs__igAlphaStateAttr__vfunc_26(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_872_0 *)(arg1))->vX()));
}

void Gap__Attrs__igAlphaStateAttr__vfunc_32(void *arg0, char arg1) {
    *(char *)((char *)arg0 + 12) = arg1;
}

void FUN_0013b800(void)
{
}

void FUN_0013b810(int a0, int a1)
{
    *(short *)((char *)a0 + 10) = a1;
}

void FUN_0013b820(void *a) {
    igObject_UserPostLoad(a);
    ((short *)a)[5] = 0;
    ((short *)a)[4] = (((VC *)a)->vX())[2];
}

void FUN_0013b860(void *p)
{
    FUN_002ff130(p);
    int t = ((A *)p)->v20()->f;
    ((short *)p)[4] = (short)t;
}

void FUN_0013b8a0(void *arg0) {
    short temp_a0;

    if ((igMetaObject_IsOfType(arg0, igAttr_GetMetaObject()) != 0) && (*(unsigned char *)((char *)(arg0) + 26) == 0)) {
        temp_a0 = GPR_00554b04;
        GPR_00554b04 = temp_a0 + 1;
        *(int *)((char *)(arg0) + 8) = (int)((int) temp_a0);
    }
}

