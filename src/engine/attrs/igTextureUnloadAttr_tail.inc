void Gap__Attrs__igTextureUnloadAttr__vfunc_24(void *arg0, int arg1) {
    int temp_a2;
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 12));
    if (temp_v1 != 0) {
        temp_a2 = *(int *)((char *)(temp_v1) + 36);
        if (temp_a2 != -1) {
            Gap__Gfx__igPsx2VisualContext__vfunc_130(arg1, temp_a2, temp_a2);
        }
    }
}

void FUN_00141840(S_141840 *arg0) {
    arg0->s10 = arg0->i16;
}

void Gap__Attrs__igTextureUnloadAttr__vfunc_17(void *arg0) {
    FUN_0013b820(arg0);
    FUN_0013b810((int)arg0, (short)*(int *)((char *)arg0 + 16));
}

void Gap__Attrs__igTextureUnloadAttr__vfunc_25(int arg0, int arg1) {
    *(int *)((char *)(arg0) + 16) = (short)arg1;
    FUN_0013b810(arg0, arg1);
}

void Gap__Attrs__igTextureUnloadAttr__vfunc_26(void) {

}

void Gap__Attrs__igTextureUnloadAttr__vfunc_31(igTextureUnloadAttrView *self, igVisualContextView *context)
{
    context->vfunc_21(22);
}

