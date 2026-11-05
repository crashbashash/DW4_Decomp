/* 0x00149050 — FUN_00149050. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00149050(void *arg0, char *arg1, int *arg2, int *arg3, int *arg4) {
    *arg1 = 1;
    if (arg2 != 0) {
        *arg2 = *(int *)((char *)(arg0) + 8);
    }
    if (arg3 != 0) {
        *arg3 = *(int *)((char *)(arg0) + 12);
    }
    if (arg4 != 0) {
        *arg4 = *(int *)((char *)(arg0) + 44);
    }
}
