/* 0x0032f840 — FUN_0032f840. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0032f840(void *arg0, void *arg1) {
    return *(int *)((char *)(arg0) + 60) == *(int *)((char *)(arg1) + 60);
}
