/* 0x00303e80 — FUN_00303e80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004e0858[4];
int *FUN_00303e80(void *arg0, int arg1) {
    int *temp_v0;
    void *temp_v0_2;

    temp_v0_2 = (void *)(*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 16) + (arg1 * 4)));
    if (temp_v0_2 == 0) {
        return 0;
    }
    temp_v0 = (int *)(*(int *)((char *)(temp_v0_2) + 8));
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return &DAT_004e0858[0];
}
