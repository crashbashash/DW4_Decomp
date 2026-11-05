/* 0x002a2f20 — FUN_002a2f20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a2f20(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 8052)) + 32);
}
