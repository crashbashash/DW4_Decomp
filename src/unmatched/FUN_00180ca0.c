/* 0x00180ca0 — FUN_00180ca0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00180ca0(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 16) = (int) (arg1 & 0xFFFF);
}
