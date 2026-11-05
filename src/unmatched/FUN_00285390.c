/* 0x00285390 — FUN_00285390. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc30)();

void FUN_00285390(void) {
    if (DAT_004bcc30 != 0) {
        DAT_004bcc30();
    }
}
