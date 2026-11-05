/* 0x001408b0 — FUN_001408b0. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad60[60]; int f3C; } S0;
int FUN_0013b820();

void FUN_001408b0(S0 *arg0) {
    if (arg0->f3C == 0) {
        arg0->f3C = 1;
    }
    FUN_0013b820();
}
