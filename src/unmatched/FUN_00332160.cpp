extern "C" {
typedef struct S { char pad0[20]; int f20; int f24; int f28; int f32; char pad36[8]; int f44; } S;
int FUN_0026d8b8(int, int, int);
int FUN_003320d0(S *, int, int, int, int, int);

int FUN_00332160(S *arg0, int arg1, int arg2) {
    if (arg0->f44 == 0) {
        arg0->f44 = FUN_003320d0(arg0, arg0->f20, arg0->f24, arg0->f28, arg0->f32, 0);
        if (arg0->f44 == 0) {
            return 0;
        }
    }
    FUN_0026d8b8(arg0->f44, arg1, arg2);
    return 1;
}
}
