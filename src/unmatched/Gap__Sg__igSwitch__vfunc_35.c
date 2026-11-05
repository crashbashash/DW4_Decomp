typedef struct P { char pad8[8]; int f8; } P;
typedef struct S { char pad28[28]; P *f28; int f32; } S;
int FUN_001b1e50();
int FUN_001c5d70();

int Gap__Sg__igSwitch__vfunc_35(S *arg0) {
    int temp_s0;
    int var_a1;
    P *temp_v0;
    int a0v;

    temp_s0 = FUN_001c5d70() & 0xFF;
    temp_v0 = arg0->f28;
    a0v = arg0->f32;
    if (temp_v0 != 0) {
        var_a1 = temp_v0->f8;
    } else {
        var_a1 = 0;
    }
    FUN_001b1e50(a0v, var_a1);
    return temp_s0;
}
