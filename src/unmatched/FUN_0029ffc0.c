/* 0x0029ffc0 — FUN_0029ffc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029ffc0(void *arg0) {
    return (((((*(unsigned char *)((char *)(arg0) + 0) << 8) | *(unsigned char *)((char *)(arg0) + 1)) << 8) | *(unsigned char *)((char *)(arg0) + 2)) << 8) | *(unsigned char *)((char *)(arg0) + 3);
}
