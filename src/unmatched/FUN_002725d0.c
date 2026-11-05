/* 0x002725d0 — FUN_002725d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0010d108();
extern int DAT_004a92f8[4];
extern int DAT_004efe28[4];
void FUN_002725d0(int arg0) {
    DAT_004a92f8[0] = arg0;
    if (arg0 == 1) {
        FUN_0010d108(&DAT_004efe28[0]);
    }
}
