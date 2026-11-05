/* 0x0026b700 — FUN_0026b700. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004a8e68)();

void FUN_0026b700(void) {
    if (DAT_004a8e68 != 0) {
        DAT_004a8e68();
    }
}
