/* 0x003313f0 — FUN_003313f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00586640[4];
int FUN_003313f0(void) {
    return DAT_00586640[0];
}
