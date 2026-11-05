/* 0x00285438 — FUN_00285438. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc40)();

void FUN_00285438(void) {
    if (DAT_004bcc40 != 0) {
        DAT_004bcc40();
    }
}
