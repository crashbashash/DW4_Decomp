/* 0x00294dc8 — FUN_00294dc8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00294a58();
extern int DAT_004bd250[4];
void FUN_00294dc8(void) {
    if (DAT_004bd250[0] != 0) {
        DAT_004bd250[0] = 0;
        FUN_00294a58();
    }
}
