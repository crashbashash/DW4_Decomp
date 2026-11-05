/* 0x00175080 — FUN_00175080. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00175080(void *arg0) {
    return *(int *)((char *)(arg0) + 1292);
}
