/* 0x002852c8 — FUN_002852c8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc1c)();

void FUN_002852c8(void) {
    if (DAT_004bcc1c != 0) {
        DAT_004bcc1c();
    }
}
