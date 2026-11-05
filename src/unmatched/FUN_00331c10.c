/* 0x00331c10 — FUN_00331c10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00586668[4];
int FUN_00331c10(void) {
    return DAT_00586668[0];
}
