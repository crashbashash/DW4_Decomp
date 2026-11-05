/* 0x002726c0 — FUN_002726c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027e298();
extern int DAT_004a92fc[4];
void FUN_002726c0(void) {
    if (DAT_004a92fc[0] == 1) {
        FUN_0027e298(1);
    }
}
