/* 0x00276040 — FUN_00276040. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
long long FUN_00275fd8();

long long FUN_00276040(void) {
    return FUN_00275fd8() >> 0x20;
}
