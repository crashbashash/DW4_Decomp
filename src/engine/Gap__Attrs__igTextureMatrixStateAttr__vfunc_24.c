typedef struct S { char p0[12]; unsigned char b; char pad[3]; int f16; } S;
int Gap__Gfx__igPsx2VisualContext__vfunc_209(int, int, unsigned char);
void Gap__Attrs__igTextureMatrixStateAttr__vfunc_24(S *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_209(arg1, arg0->f16, arg0->b);
}
