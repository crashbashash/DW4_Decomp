/* 0x00275718 — FUN_00275718. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
long long FUN_00275740();

long long FUN_00275718(void) {
    return (long long) (FUN_00275740() << 0x20) >> 0x20;
}
