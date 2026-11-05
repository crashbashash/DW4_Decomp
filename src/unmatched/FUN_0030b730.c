/* 0x0030b730 — FUN_0030b730. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00230298();
int FUN_0030b7e0(int, int, int);

void FUN_0030b730(int arg0, int arg1) {
    FUN_0030b7e0(arg0, arg1, FUN_00230298());
}
