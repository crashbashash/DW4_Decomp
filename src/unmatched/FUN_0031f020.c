/* 0x0031f020 — FUN_0031f020. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0031f020(void *arg0) {
    return *(int *)((char *)(arg0) + 180);
}
