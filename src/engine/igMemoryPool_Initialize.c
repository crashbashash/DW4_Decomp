/* 0x002eff70 — igMemoryPool_Initialize. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObject_InitHeader();
extern int DAT_0052f620[4];
int **igMemoryPool_Initialize(int **arg0) {
    igObject_InitHeader();
    *arg0 = &DAT_0052f620[0];
    return arg0;
}
