#include "dw4/typecast.h"
extern "C" {
int FUN_0026b728(int);
int FUN_0026bc60(int);
int FUN_00338df0(int, int);
extern int DAT_00587760[4];
typedef struct S { char pad8[8]; int *f8; int f12; int f16; int f20; } S;
int Gap__igCriMovieCodec__vfunc_24(int arg0, void *arg1) {
    S *var_s0;
    int temp_a0;

    var_s0 = (S *)dw4_cast_or_null((char *)*(int *)((char *)(arg1) + 96), DAT_00587760);
    if (var_s0 != 0) {
        temp_a0 = var_s0->f16;
        if (temp_a0 != 0) {
            FUN_0026bc60(temp_a0);
            FUN_0026b728(var_s0->f16);
            FUN_00338df0(arg0, var_s0->f20);
            var_s0->f16 = 0;
            var_s0->f20 = 0;
        }
        ((int (*)(int *))*(int *)((char *)(*(int *)var_s0->f8) + 20))(var_s0->f8);
        FUN_00338df0(arg0, var_s0->f12);
        var_s0->f8 = 0;
        var_s0->f12 = 0;
        return 1;
    }
    return 0;
}
}
