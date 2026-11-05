/* 0x002980c0 — FUN_002980c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002968c0();
int FUN_00297810();
int FUN_0029a320();
int FUN_002b3d60();
extern int DAT_004f4300[4];
void FUN_002980c0(int arg0, int arg1) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f4300[0]);
        return;
    }
    FUN_002b3d60(FUN_00297810(arg0), arg1);
}
