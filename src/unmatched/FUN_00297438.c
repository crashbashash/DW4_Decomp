/* 0x00297438 — FUN_00297438. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002963a8();
int FUN_002968c0();
int FUN_0029a320();
int FUN_002aa548();
extern int DAT_004f3f98[4];
void FUN_00297438(int arg0, int arg1) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f3f98[0]);
        return;
    }
    FUN_002aa548(FUN_002963a8(arg0), arg1);
}
