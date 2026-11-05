extern "C" {
struct Q { char pad[16]; short f16; short f18; };
struct T { char pad[16]; struct Q **f16; };
struct S { char pad[44]; int f44; };
int FUN_0026d5f0(int, short, short);
int FUN_0026d7a0(int, int);
int FUN_003320d0(S *, int, int, int, int, int);
int FUN_00333440(int);
extern struct T *DAT_00587620[4];
int FUN_003321f0(struct S *arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    int temp_v0;
    struct Q *temp_v0_2;

    arg0->f44 = FUN_003320d0(arg0, arg2, arg3, arg4, arg5, 1);
    temp_v0 = FUN_00333440(arg1);
    if (temp_v0 != -1) {
        temp_v0_2 = DAT_00587620[0]->f16[temp_v0];
        FUN_0026d5f0(arg0->f44, temp_v0_2->f16, temp_v0_2->f18);
    } else {
        FUN_0026d7a0(arg0->f44, arg1);
    }
    return 1;
}
}
