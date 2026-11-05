/* 0x307660 — FUN_00307660, m2c draft + manual source-shape fix (finding #663),
 * verified byte-identical to retail by tools/verify.py. */
void *FUN_00307c10();
int FUN_0030b720();
extern int DAT_004f95c0[4];
int FUN_00307660(void *arg0, int arg1, int arg2, int arg3) {
    void *temp_v0;
    temp_v0 = (void *)FUN_00307c10(arg0, arg1, arg2, 1);
    if (temp_v0 == 0) return 0;
    FUN_0030b720(*(int *)((char *)(temp_v0) + 12), arg3, &DAT_004f95c0[0]);
    return 1;
}
