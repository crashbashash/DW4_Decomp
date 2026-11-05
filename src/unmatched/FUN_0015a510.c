/* 0x0015a510 — FUN_0015a510. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0015a510(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 12) = (int) (arg1 & 0xFFFF);
}
