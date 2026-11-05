/* 0x00331c90 — FUN_00331c90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00586880[4];
int FUN_00331c90(void) {
    return DAT_00586880[0];
}
