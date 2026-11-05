/* 0x002e1710 - igEventTracker vfunc 40. Hidden-return virtual query on two sub-objects (slots 108/100/116) with a 7-argument pass-through (stack argument 0(sp)); the result type has a constructor so the return writes straight through the saved hidden pointer; alternate compiler -O3, exceptions off. */
struct R { int a; R(int x) : a(x) {} };
struct X { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v100(); virtual void d104(); virtual R v108(int, int, int, int *, int, int, int *); virtual void d112(); virtual void v116(int, int, int, int, int); };
struct T { char p[76]; X *f76; char q[12]; X *f92; };
extern "C" {
int FUN_002eb210(X *);
extern int DAT_004fb418[4];
extern int DAT_00586e00[4];
extern int DAT_00586e08[4];
extern int DAT_00586e10[4];
R Gap__Core__igEventTracker__vfunc_40(T *arg1, int arg2, int arg3, int arg4, int *arg5, int arg6, int arg7, int *arg8);
}
R Gap__Core__igEventTracker__vfunc_40(T *arg1, int arg2, int arg3, int arg4, int *arg5, int arg6, int arg7, int *arg8) {
    int s0;
    if (FUN_002eb210(arg1->f76) != 0) {
        s0 = arg1->f76->v108(arg2, arg3, arg4, arg5, arg6, arg7, arg8).a;
        if (s0 == DAT_004fb418[0]) {
            if (arg1->f92->v100() != 0) {
                s0 = arg1->f92->v108(arg2, arg3, arg4, arg5, arg6, arg7, arg8).a;
                arg1->f76->v116(arg2, arg3, *arg5, arg6, *arg8);
                DAT_00586e08[0] = DAT_00586e08[0] + 1;
                goto join;
            }
        }
        DAT_00586e10[0] += 1;
    } else {
        s0 = arg1->f92->v108(arg2, arg3, arg4, arg5, arg6, arg7, arg8).a;
        DAT_00586e08[0] = DAT_00586e08[0] + 1;
    }
join:
    DAT_00586e00[0] += 1;
    return R(s0);
}
