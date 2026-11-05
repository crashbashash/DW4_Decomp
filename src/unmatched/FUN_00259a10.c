/* 0x00259a10 — FUN_00259a10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004ec890[4];
int *FUN_00259a10(void) {
    return &DAT_004ec890[0];
}
