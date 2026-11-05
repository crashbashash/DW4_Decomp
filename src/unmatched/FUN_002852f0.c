/* 0x002852f0 — FUN_002852f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc20)();

void FUN_002852f0(void) {
    if (DAT_004bcc20 != 0) {
        DAT_004bcc20();
    }
}
