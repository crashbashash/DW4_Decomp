/* The first field read is unsigned so it is loaded from a0 before the copy to s1. */
int Gap__Gfx__igPsx2VisualContext__vfunc_245(int, int);
int Gap__Gfx__igPsx2VisualContext__vfunc_243(int, float);
int Gap__Gfx__igPsx2VisualContext__vfunc_247(int, void *);
int Gap__Gfx__igPsx2VisualContext__vfunc_249(int, float);
int Gap__Gfx__igPsx2VisualContext__vfunc_251(int, float);
void Gap__Attrs__igFogAttr__vfunc_24(char *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_245(arg1, *(unsigned int *)(arg0 + 12));
    Gap__Gfx__igPsx2VisualContext__vfunc_243(arg1, *(float *)(arg0 + 24));
    Gap__Gfx__igPsx2VisualContext__vfunc_247(arg1, arg0 + 0x1C);
    Gap__Gfx__igPsx2VisualContext__vfunc_249(arg1, *(float *)(arg0 + 16));
    Gap__Gfx__igPsx2VisualContext__vfunc_251(arg1, *(float *)(arg0 + 20));
}
