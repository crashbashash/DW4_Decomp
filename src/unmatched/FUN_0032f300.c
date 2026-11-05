/* 0x0032f300 — FUN_0032f300. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int * DAT_00587218[4];
extern int DAT_00587380[4];
void FUN_0032f300(void) {
    if (DAT_00587218[0] == 0) {
        DAT_00587218[0] = &DAT_00587380[0];
    }
}
