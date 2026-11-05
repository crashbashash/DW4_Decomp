/* 0x00272fb8 — FUN_00272fb8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00272fb8(void *arg0) {
    *(int *)((char *)(arg0) + 60) = 0;
    *(char *)((char *)(arg0) + 1) = 1;
}
