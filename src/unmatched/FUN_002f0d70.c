/* 0x002f0d70 — FUN_002f0d70. Banked by tools/retype_struct_member.py (shape: leadfn1):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad4[4]; int f4; } S0;
int igObject_Destroy();

void FUN_002f0d70(int dummy0, S0 *arg1) {
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 - 1));
        if (((unsigned long long) ((long long) arg1->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(arg1);
        }
    }
}
