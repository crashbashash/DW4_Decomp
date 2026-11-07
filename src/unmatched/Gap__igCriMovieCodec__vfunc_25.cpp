extern "C" {
typedef struct V { int *vt; } V;
typedef struct D { char pad8[8]; V *f8; char pad[4]; int f16; } D;
typedef struct A { char pad[24]; int f24; char pad2[48]; int f76; char pad3[16]; D *f96; } A;
int FUN_0026ce40(int, int);
int FUN_0026cf70(int);
int FUN_00295468(V *);
int igObject_IsKindOf(D *, int);
extern int DAT_00587760[4];
int Gap__igCriMovieCodec__vfunc_25(int arg0, A *arg1) {
    V *temp_a0;
    D *var_s0;

    var_s0 = arg1->f96;
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_00587760[0]) != 0)) {
        asm { nop }
    } else {
        var_s0 = 0;
    }
    if (var_s0 != 0) {
        arg1->f76 = 0;
        if (arg1->f24 == 2) {
            if (FUN_0026cf70(var_s0->f16) != 0) {
                FUN_0026ce40(var_s0->f16, 0);
            }
        } else if (FUN_00295468(var_s0->f8) == 1) {
            temp_a0 = var_s0->f8;
            ((int (*)(V *, int))temp_a0->vt[10])(temp_a0, 0);
        }
        return 1;
    }
    return 0;
}
}
