/* 0x0013c6b0 — FUN_0013c6b0. Banked by tools/retype_struct_member.py (shape: width):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int FUN_001931b0();
float FUN_00230e50();
int Gap__Core__igObject__vfunc_09();

void FUN_0013c6b0(void *arg0) {
    Gap__Core__igObject__vfunc_09();
    *(int *)((char *)(arg0) + 60) = FUN_001931b0((char *)arg0 + 0x10, 1);
    *(float *)((char *)(arg0) + 64) = FUN_00230e50(*(long long *)((char *)(arg0) + 48));
}
