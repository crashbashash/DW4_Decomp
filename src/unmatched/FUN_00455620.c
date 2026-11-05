/* 0x00455620 — FUN_00455620. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
unsigned char FUN_00455620(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 15);
}
