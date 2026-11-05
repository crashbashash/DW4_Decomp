/* 0x002ace60 — FUN_002ace60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002ace60(void *arg0, int arg1, int arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 13864));
    if (temp_v1 != 0) {
        if (*(int *)((char *)(temp_v1) + 3512) < 0) {
            *(int *)((char *)(temp_v1) + 3512) = arg1;
        }
        if (*(int *)((char *)(temp_v1) + 3516) < 0) {
            *(int *)((char *)(temp_v1) + 3516) = arg2;
        }
    }
}
