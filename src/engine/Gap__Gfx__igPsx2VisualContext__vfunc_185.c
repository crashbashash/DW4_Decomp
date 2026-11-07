struct S_arg0 { char pad0[104]; int f104; char pad6C[808]; int f916; int f920; int f924; int f928; float f932; float f936; };
int FUN_0016a520();
int FUN_0020dba0(int, int, int, int, float, float);

void Gap__Gfx__igPsx2VisualContext__vfunc_185(struct S_arg0 *arg0, int arg1, int arg2, int arg3, int arg4, float fparg0, float fparg1) {
    arg0->f916 = arg1;
    arg0->f920 = arg2;
    arg0->f924 = arg3;
    arg0->f928 = arg4;
    arg0->f932 = fparg0;
    arg0->f936 = fparg1;
    if (arg0->f104 == 0) {
        FUN_0016a520();
    }
    FUN_0020dba0(arg1, arg2, arg3, arg4, 1.0f - arg0->f932, 1.0f - arg0->f936);
}
