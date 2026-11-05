/* 0x00154e00 — FUN_00154e00. Banked by tools/retype_struct_member.py (shape: leadcall0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad20[20]; int f14; } S0;
int FUN_00300f50();

void FUN_00154e00(S0 *arg0) {
    int temp_a1;

    temp_a1 = arg0->f14;
    if (temp_a1 != 0) {
        FUN_00300f50(arg0, temp_a1);
        arg0->f14 = 0;
    }
}
