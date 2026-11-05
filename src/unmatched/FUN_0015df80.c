/* 0x0015df80 — FUN_0015df80. Banked by tools/retype_struct_member.py (shape: struct4):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad24[24]; int f18; } S0;
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
typedef struct S_temp_v0 { char pad4[4]; int f4; } S_temp_v0;
int igObject_Destroy();
void *igObject_GetAllocator();
int Gap__Core__igObject__vfunc_11();

void FUN_0015df80(S0 *arg0) {
    S_temp_a0 *temp_a0;
    S_temp_v0 *temp_v0;
    Gap__Core__igObject__vfunc_11();
    temp_v0 = (void *)(igObject_GetAllocator(arg0));
    if (temp_v0 != 0) {
        temp_v0->f4 = (int)((int) (temp_v0->f4 + 1));
    }
    temp_a0 = (void *)(arg0->f18);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f18 = (int)(temp_v0);
}
