/* 0x00285460 — FUN_00285460. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc44)();

void FUN_00285460(void) {
    if (DAT_004bcc44 != 0) {
        DAT_004bcc44();
    }
}
