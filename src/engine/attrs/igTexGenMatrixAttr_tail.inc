void FUN_001404f0(void *arg0) {
    *(short *)((char *)(arg0) + 10) = (short) *(int *)((char *)(arg0) + 76);
}

void Gap__Attrs__igTexGenMatrixAttr__vfunc_25(int arg0, int arg1) {
    *(int *)((char *)(arg0) + 76) = (short)arg1;
    FUN_0013b810(arg0, arg1);
}

void Gap__Attrs__igTexGenMatrixAttr__vfunc_17(void *arg0) {
    FUN_0013b820(arg0);
    FUN_0013b810((int)arg0, *(short *)((char *)(arg0) + 76));
}

void Gap__Attrs__igTexGenMatrixAttr__vfunc_24(char * arg0, int arg1) {
    FUN_00173ed0(arg1, 14, (arg0 + 12));
}

void Gap__Attrs__igTexGenMatrixAttr__vfunc_26(igTexGenMatrixAttr *self, void *context)
{
    float m[16];

    igMatrix44f_SetIdentity(m);
    FUN_00173fd0(context, 14, m);
    Matrix44_Copy(self->m, m);
}

