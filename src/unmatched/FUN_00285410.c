/* 0x00285410 — FUN_00285410. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc3c)();

void FUN_00285410(void) {
    if (DAT_004bcc3c != 0) {
        DAT_004bcc3c();
    }
}
