/* 0x002aec58 — FUN_002aec58. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002aec58(void *arg0, int *arg1, int *arg2) {
    int temp_v1;

    temp_v1 = *(int *)((char *)(arg0) + 72);
    if ((temp_v1 != 4) && (temp_v1 != -4) && (temp_v1 != 6) && (temp_v1 != -6)) {
        *arg1 = -1;
        *arg2 = 1;
        return 0;
    }
    return 1;
}
