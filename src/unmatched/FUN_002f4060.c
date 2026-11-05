/* 0x002f4060 — FUN_002f4060. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002f4060(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 12) = arg1;
}
