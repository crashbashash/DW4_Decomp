/* 0x002941e0 — FUN_002941e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002963a8();
int FUN_002968c0();
int FUN_0029a320();
int FUN_002a8940();
extern int DAT_004f3208[4];
int FUN_002941e0(int arg0) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f3208[0]);
        return 0;
    }
    return FUN_002a8940(FUN_002963a8(arg0));
}
