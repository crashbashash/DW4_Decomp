/* 0x00285340 — FUN_00285340. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc28)();

void FUN_00285340(void) {
    if (DAT_004bcc28 != 0) {
        DAT_004bcc28();
    }
}
