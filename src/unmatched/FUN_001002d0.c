/* 0x001002d0 — FUN_001002d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00230c78();

int FUN_001002d0(void) {
    return FUN_00230c78() != 0;
}
