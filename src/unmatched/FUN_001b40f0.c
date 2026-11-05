/* 0x001b40f0 — FUN_001b40f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001b40f0(void *arg0, int arg1) {
    if (arg1 >= 8) {
        return 0;
    }
    return *(unsigned char *)((char *)(arg0) + 64) & (1 << arg1) & 0xFF;
}
