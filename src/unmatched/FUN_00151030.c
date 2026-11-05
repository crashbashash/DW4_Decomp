/* 0x00151030 — FUN_00151030. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00151030(void *arg0) {
    *(int *)((char *)(arg0) + 20) = 0;
    *(char *)((char *)(arg0) + 0) = 0;
    *(char *)((char *)(arg0) + 1) = 0;
    *(int *)((char *)(arg0) + 12) = 0;
    *(int *)((char *)(arg0) + 16) = 0;
    return arg0;
}
