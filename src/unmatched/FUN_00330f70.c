/* 0x00330f70 — FUN_00330f70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
unsigned char FUN_00330f70(void *arg0) {
    return *(int *)((char *)(arg0) + 141);
}
