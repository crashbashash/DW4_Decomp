/* 0x00207450 — FUN_00207450. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00207450(int arg0) {
    *(int *)0x56C000 = arg0;
    *(int *)0x56C008 = 0;
}
