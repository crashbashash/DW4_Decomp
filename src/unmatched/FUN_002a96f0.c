/* 0x002a96f0 — FUN_002a96f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00108cc8();
int FUN_0028b460();
extern int DAT_004beb10[4];
extern int DAT_00585630[4];
void FUN_002a96f0(void) {
    if (DAT_004beb10[0] != 0) {
        FUN_00108cc8();
        FUN_0028b460(&DAT_00585630[0], 0, 0x48);
    }
}
