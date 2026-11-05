/* 0x001e07a0 - FUN_001e07a0. Array walk with a three-way result; alternate compiler. Verified byte-identical by tools/verify.py. */
extern "C" { int FUN_001e04c0(...); }
struct L { char p[8]; int n; char q[4]; int *arr; };
struct S { char p[28]; L *f28; };
extern "C" int FUN_001e07a0(int arg0, S *arg1);
int FUN_001e07a0(int arg0, S *arg1) {
    L *temp_v0 = arg1->f28;
    int *var_s0;
    int *temp_s2;
    int r;
    if (temp_v0 != 0) {
        var_s0 = temp_v0->arr;
        temp_s2 = var_s0 + temp_v0->n;
        for (; var_s0 < temp_s2; var_s0++) {
            r = FUN_001e04c0(arg0, *var_s0);
            if (r == 1) return 0;
            if (r == 2) return 2;
        }
    }
    return 0;
}
