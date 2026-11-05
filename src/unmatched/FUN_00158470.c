/* 0x00158470 — FUN_00158470. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00158470(void *arg0) {
    *(int *)((char *)arg0 + 24) = 0x66;
}
