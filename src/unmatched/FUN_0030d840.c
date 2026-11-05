/* 0x0030d840 — FUN_0030d840. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
unsigned short FUN_0030d840(void *arg0) {
    return *(int *)((char *)(arg0) + 20);
}
