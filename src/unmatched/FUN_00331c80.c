/* 0x00331c80 — FUN_00331c80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00585b60[4];
int FUN_00331c80(void) {
    return DAT_00585b60[0];
}
