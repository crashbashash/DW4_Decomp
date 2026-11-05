/* 0x00285368 — FUN_00285368. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc2c)();

void FUN_00285368(void) {
    if (DAT_004bcc2c != 0) {
        DAT_004bcc2c();
    }
}
