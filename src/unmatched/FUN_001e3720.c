/* 0x001e3720 — FUN_001e3720. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00586858[4];
int FUN_001e3720(void) {
    return DAT_00586858[0];
}
