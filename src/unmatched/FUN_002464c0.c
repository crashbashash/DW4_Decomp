/* 0x002464c0 — FUN_002464c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00245f50();
extern unsigned char DAT_00554be4[4];
extern int DAT_0056df40[4];
extern int DAT_0056df48[4];
void FUN_002464c0(int arg0) {
    if (DAT_00554be4[0] != 0) {
        FUN_00245f50(DAT_0056df48[0], arg0);
        return;
    }
    DAT_0056df40[0] = arg0;
}
