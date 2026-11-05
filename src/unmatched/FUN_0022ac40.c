/* 0x0022ac40 — FUN_0022ac40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0022ad00();

int FUN_0022ac40(void) {
    return FUN_0022ad00() != 0;
}
