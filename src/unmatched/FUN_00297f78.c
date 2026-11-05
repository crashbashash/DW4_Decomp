/* 0x00297f78 — FUN_00297f78. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002968c0();
int FUN_00297810();
int FUN_0029a320();
int FUN_002b3c08();
extern int DAT_004f4288[4];
void FUN_00297f78(int arg0, int arg1, int arg2) {
    if (FUN_002968c0() == 0) {
        FUN_0029a320(&DAT_004f4288[0]);
        return;
    }
    FUN_002b3c08(FUN_00297810(arg0), arg1, arg2);
}
