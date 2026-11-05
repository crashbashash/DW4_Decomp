/* 0x00175090 — FUN_00175090. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad1296[1296]; int f510; } S0;
extern int DAT_005609c8[4];
void FUN_00175090(S0 *arg0, int arg1) {
    if (arg0->f510 == arg1) {
        DAT_005609c8[0] += 1;
    }
    arg0->f510 = arg1;
}
