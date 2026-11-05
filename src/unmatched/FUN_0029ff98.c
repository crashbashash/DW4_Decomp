/* 0x0029ff98 — FUN_0029ff98. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029ffc0();

int FUN_0029ff98(void) {
    return FUN_0029ffc0() == 0x1BF;
}
