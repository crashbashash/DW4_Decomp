/* 0x002a8c70 — FUN_002a8c70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002a8c70(long long *arg0, long long arg1, long long arg2, long long arg3) {
    *arg0 = (arg1 << 0x20) | ((unsigned long long) (arg2 << 0x20) >> 4) | ((unsigned long long) (arg3 << 0x20) >> 0x20);
}
