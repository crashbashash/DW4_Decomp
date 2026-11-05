/* 0x00331780 — FUN_00331780. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00586780[4];
int FUN_00331780(void) {
    return DAT_00586780[0];
}
