/* 0x00293788 — FUN_00293788. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002937d8();
int FUN_002968c0();
int FUN_0029a320();
extern int DAT_004f30d0[4];
int FUN_00293788(int arg0) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f30d0[0]);
        return 0;
    }
    return FUN_002937d8(arg0);
}
