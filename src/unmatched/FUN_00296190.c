/* 0x00296190 — FUN_00296190. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memcpy();

int FUN_00296190(int arg0, int arg1, int arg2) {
    memcpy(arg2 + 0x70000000, arg0, arg1);
    return 0;
}
