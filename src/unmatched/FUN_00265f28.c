/* 0x00265f28 — FUN_00265f28. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004a52c8[4];
void FUN_00265f28(void) {
    DAT_004a52c8[0] += 1;
}
