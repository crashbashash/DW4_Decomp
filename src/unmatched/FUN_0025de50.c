/* 0x0025de50 — FUN_0025de50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0025de50(void *arg0) {
    if (*(int *)((char *)(arg0) + 4) == 0) {
        *(int *)((char *)(arg0) + 4) = 1;
    }
}
