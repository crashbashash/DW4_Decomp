/* 0x00100360 — FUN_00100360. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00230c78();

int FUN_00100360(void) {
    return FUN_00230c78() >= 0;
}
