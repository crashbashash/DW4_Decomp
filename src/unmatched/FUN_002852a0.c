/* 0x002852a0 — FUN_002852a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc14)();

void FUN_002852a0(void) {
    if (DAT_004bcc14 != 0) {
        DAT_004bcc14();
    }
}
