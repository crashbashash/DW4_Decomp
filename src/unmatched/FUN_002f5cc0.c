/* 0x002f5cc0 — FUN_002f5cc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004fb410[4];
void FUN_002f5cc0(int *arg0) {
    *arg0 = DAT_004fb410[0];
}
