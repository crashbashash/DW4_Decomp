/* 0x00290d68 — FUN_00290d68. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0028b350();
int FUN_00290db8();
extern int DAT_004bccd4[4];
extern int DAT_004bcce0[4];
void FUN_00290d68(int arg0) {
    FUN_00290db8();
    if (arg0 != 0) {
        FUN_0028b350(arg0, &DAT_004bcce0[0], 0x100);
        DAT_004bccd4[0] = arg0 + 0x180;
    }
}
