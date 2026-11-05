/* 0x004629c0 — FUN_004629c0. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad12[12]; int fC; char pad44[28]; int f2C; char pad176[128]; int fB0; } S0;
int FUN_00236f30();
int FUN_004542a0();

void FUN_004629c0(S0 *arg0) {
    void *temp_a0;

    temp_a0 = (void *)(arg0->fC);
    if (temp_a0 != 0) {
        FUN_00236f30(temp_a0, *(int *)((char *)(*(int *)((char *)(arg0) + 44)) + 8));
        FUN_004542a0(*(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 32), arg0->f2C);
        arg0->fB0 = 2;
    }
}
