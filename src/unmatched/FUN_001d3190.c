/* 0x001d3190 — FUN_001d3190. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001d3190(void *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 16));
    if (temp_v0 != 0) {
        return *(int *)((char *)(temp_v0) + 8);
    }
    return 0;
}
