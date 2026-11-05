/* 0x002851f8 — FUN_002851f8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int (*DAT_004bcc08)();

void FUN_002851f8(void) {
    if (DAT_004bcc08 != 0) {
        DAT_004bcc08();
    }
}
