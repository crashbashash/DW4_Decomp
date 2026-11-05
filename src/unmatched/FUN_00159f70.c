/* 0x00159f70 — FUN_00159f70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00159f70(int arg0) {
    return (unsigned int) ((arg0 - 0x8000) - 0x8000) < 3U;
}
