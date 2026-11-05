/* 0x002851d0 — FUN_002851d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc04)();

void FUN_002851d0(void) {
    if (DAT_004bcc04 != 0) {
        DAT_004bcc04();
    }
}
