/* 0x004542e0 — FUN_004542e0. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad12[12]; int fC; } S0;
int FUN_002d7760();

void FUN_004542e0(S0 *arg0, int arg1, int arg2) {
    int sp1C;

    FUN_002d7760(&sp1C, arg0->fC, arg1, arg2);
}
