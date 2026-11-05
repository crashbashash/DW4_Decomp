/* 0x0030b420 — FUN_0030b420. Banked by tools/retype_struct_member.py (shape: leadcall0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad8[8]; int f8; int fC; } S0;
int FUN_00300f50();

void FUN_0030b420(S0 *arg0) {
    int temp_a1;

    temp_a1 = arg0->f8;
    if (temp_a1 != 0) {
        FUN_00300f50(arg0, temp_a1);
    }
    arg0->f8 = 0;
    arg0->fC = 0;
}
