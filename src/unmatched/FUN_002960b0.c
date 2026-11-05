/* 0x002960b0 — FUN_002960b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memcpy();

int FUN_002960b0(int arg0, int arg1, int arg2) {
    memcpy(arg2, arg0 + 0x70000000, arg1);
    return 0;
}
