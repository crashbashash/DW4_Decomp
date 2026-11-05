/* 0x0026b6d8 — FUN_0026b6d8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004a8e60)();

void FUN_0026b6d8(void) {
    if (DAT_004a8e60 != 0) {
        DAT_004a8e60();
    }
}
