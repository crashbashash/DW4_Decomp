/* 0x002a99b8 — FUN_002a99b8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a99b8(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 8120)) + 4476);
}
