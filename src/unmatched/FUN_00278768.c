/* 0x00278768 — FUN_00278768. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004b0e08[4];
void FUN_00278768(void) {
    DAT_004b0e08[0] -= 1;
}
