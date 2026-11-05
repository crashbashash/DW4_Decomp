/* 0x002f0860 — FUN_002f0860. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004fb418[4];
void FUN_002f0860(int *arg0) {
    *arg0 = DAT_004fb418[0];
}
