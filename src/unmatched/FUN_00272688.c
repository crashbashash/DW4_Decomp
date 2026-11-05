/* 0x00272688 — FUN_00272688. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027e220();
extern int DAT_004a92fc[4];
void FUN_00272688(void) {
    if (DAT_004a92fc[0] == 1) {
        FUN_0027e220(1);
    }
}
