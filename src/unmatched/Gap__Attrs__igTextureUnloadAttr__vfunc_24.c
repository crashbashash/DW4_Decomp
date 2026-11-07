int Gap__Gfx__igPsx2VisualContext__vfunc_130();

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
