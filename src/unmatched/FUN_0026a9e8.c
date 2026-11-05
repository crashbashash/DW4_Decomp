/* 0x0026a9e8 — FUN_0026a9e8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026a9e8(void *arg0, int arg1) {
    *(int *)((char *)arg0 + 44) = arg1;
    return 1;
}
