int Gap__Gfx__igPsx2VisualContext__vfunc_176();
int Gap__Gfx__igPsx2VisualContext__vfunc_178();
int Gap__Gfx__igPsx2VisualContext__vfunc_181(int, float);
int Gap__Gfx__igPsx2VisualContext__vfunc_183();

void Gap__Attrs__igClearAttr__vfunc_24(void *arg0, int arg1) {
    int temp_a1;

    Gap__Gfx__igPsx2VisualContext__vfunc_181(arg1, *(float *)((char *)(arg0) + 64));
    Gap__Gfx__igPsx2VisualContext__vfunc_178(arg1, *(int *)((char *)(arg0) + 60));
    Gap__Gfx__igPsx2VisualContext__vfunc_183(arg1, *(int *)((char *)(arg0) + 56));
    temp_a1 = *(int *)((char *)(arg0) + 12);
    if (temp_a1 != 0) {
        Gap__Gfx__igPsx2VisualContext__vfunc_176(arg1, temp_a1);
    }
}
