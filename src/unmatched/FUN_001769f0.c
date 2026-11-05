/* 0x001769f0 — FUN_001769f0. Banked by tools/retype_struct_member.py (shape: leadcall1):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int Gap__Core__igPrimLengthArray1_1__vfunc_59();

void FUN_001769f0(void *arg0) {
    int temp_a1;

    if (!(*(int *)((char *)(*(int *)((char *)(arg0) + 24)) + 20) & 0x10)) {
        Gap__Core__igPrimLengthArray1_1__vfunc_59();
        return;
    }
    temp_a1 = *(int *)((char *)(arg0) + 36);
    if (temp_a1 == 1) {
        Gap__Core__igPrimLengthArray1_1__vfunc_59(arg0, temp_a1);
    }
    *(char *)((char *)(arg0) + 32) = 0;
}
