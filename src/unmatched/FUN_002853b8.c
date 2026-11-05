/* 0x002853b8 — FUN_002853b8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc34)();

void FUN_002853b8(void) {
    if (DAT_004bcc34 != 0) {
        DAT_004bcc34();
    }
}
