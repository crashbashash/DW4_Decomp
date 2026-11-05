/* 0x0017a870 — FUN_0017a870. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad1524[1524]; int f5F4; int f5F8; int f5FC; } S0;
int FUN_0020c9f0();

void FUN_0017a870(S0 *arg0, int arg1) {
    int temp_a0;
    int temp_a0_2;
    int temp_a0_3;

    if (arg1 == 0) {
        temp_a0 = arg0->f5F4;
        if (temp_a0 != 0) {
            FUN_0020c9f0(temp_a0);
            arg0->f5F4 = 0;
        }
        temp_a0_2 = arg0->f5F8;
        if (temp_a0_2 != 0) {
            FUN_0020c9f0(temp_a0_2);
            arg0->f5F8 = 0;
        }
        temp_a0_3 = arg0->f5FC;
        if (temp_a0_3 != 0) {
            FUN_0020c9f0(temp_a0_3);
            arg0->f5FC = 0;
        }
    }
}
