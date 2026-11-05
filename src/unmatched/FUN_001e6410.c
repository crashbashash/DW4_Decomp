/* 0x001e6410 — FUN_001e6410. Banked by tools/retype_struct_member.py (shape: struct4):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad24[24]; int f18; } S0;
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
typedef struct S_temp_s0 { char pad4[4]; int f4; } S_temp_s0;
int igObject_Destroy();

void FUN_001e6410(S0 *arg0, void **arg1) {
    S_temp_a0 *temp_a0;
    S_temp_s0 *temp_s0;
    temp_s0 = (void *)(*arg1);
    if (temp_s0 != 0) {
        temp_s0->f4 = (int)((int) (temp_s0->f4 + 1));
    }
    temp_a0 = (void *)(arg0->f18);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f18 = (int)(temp_s0);
}
