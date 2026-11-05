/* 0x00457e90 — FUN_00457e90. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad8[8]; int f8; } S0;
int FUN_004576d0();
int FUN_004577f0();

void FUN_00457e90(S0 *arg0, int arg1) {
    int temp_a0;
    int temp_a0_2;

    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        FUN_004577f0(temp_a0, arg0);
    }
    arg0->f8 = arg1;
    temp_a0_2 = arg0->f8;
    if (temp_a0_2 != 0) {
        FUN_004576d0(temp_a0_2, arg0);
    }
}
