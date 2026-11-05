/* 0x0018fba0 — FUN_0018fba0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0018fba0(void *arg0) {
    return *(int *)(*(int *)((char *)((*(void **)0x561170)) + 16) + (*(int *)((char *)arg0 + 8) * 4));
}
