/* 0x00245080 — FUN_00245080. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00245080(void *arg0, int arg1, int arg2, int arg3) {
    unsigned int temp_a4;
    void **temp_a1;
    void *temp_v1;

    temp_a4 = *(int *)((char *)(arg0) + 0);
    temp_a1 = (void **)(arg1 + (((arg2 - 1) & (temp_a4 ^ (temp_a4 >> arg3))) * 4));
    *(int *)((char *)(arg0) + 4) = (int)((int) *temp_a1);
    temp_v1 = (void *)(*temp_a1);
    if (temp_v1 != 0) {
        *(int *)((char *)(temp_v1) + 8) = (int)(arg0);
    }
    *(int *)((char *)(arg0) + 8) = 0;
    *temp_a1 = arg0;
}
