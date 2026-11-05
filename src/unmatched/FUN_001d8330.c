/* 0x001d8330 — FUN_001d8330. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001d8330(void *arg0, unsigned int arg1) {
    return ((1 << (arg1 & 0x1F)) & *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 52)) + 16) + ((arg1 >> 5) * 4))) != 0;
}
