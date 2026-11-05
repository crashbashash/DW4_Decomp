/* 0x0025b418 — FUN_0025b418. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025f2d0();
int FUN_0025f2e8();
int memset();

void FUN_0025b418(int arg0) {
    if (arg0 != 0) {
        FUN_0025f2d0();
        memset(arg0, 0, 0x30);
        FUN_0025f2e8();
    }
}
