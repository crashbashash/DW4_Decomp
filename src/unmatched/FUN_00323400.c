/* 0x00323400 — FUN_00323400. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004fb418[4];
void FUN_00323400(int *arg0) {
    *arg0 = DAT_004fb418[0];
}
