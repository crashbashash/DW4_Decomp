/* 0x001bafb0 — FUN_001bafb0. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int FUN_001b7770();
int FUN_001b7920();
int FUN_001b7af0();
int FUN_001e04c0();
int FUN_001e07a0();
extern int DAT_004e0858[4];
struct S { char pad[8]; int *f8; };
int FUN_001bafb0(int arg0, struct S *arg1) {
    int *var_a1;
    int *var_a1_2;
    int *var_a1_3;
    int temp_v0;
    int var_s0;

    var_a1 = arg1->f8;
    var_a1 = var_a1 ? var_a1 : &DAT_004e0858[0];
    temp_v0 = FUN_001b7af0(arg0, var_a1);
    if (temp_v0 != 0) {
        var_a1_2 = arg1->f8;
        var_a1_2 = var_a1_2 ? var_a1_2 : &DAT_004e0858[0];
        FUN_001b7770(arg0, var_a1_2, 0);
        var_s0 = FUN_001e04c0(arg0, temp_v0);
        var_a1_3 = arg1->f8;
        var_a1_3 = var_a1_3 ? var_a1_3 : &DAT_004e0858[0];
        FUN_001b7920(arg0, var_a1_3);
    } else {
        var_s0 = FUN_001e07a0(arg0, arg1);
    }
    return var_s0;
}
