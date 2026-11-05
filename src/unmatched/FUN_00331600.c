/* 0x00331600 — FUN_00331600. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_005868a8[4];
int FUN_00331600(void) {
    return DAT_005868a8[0];
}
