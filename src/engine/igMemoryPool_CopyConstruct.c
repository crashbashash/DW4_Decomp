/* 0x002efff0 — igMemoryPool_CopyConstruct. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObject_CopyConstructHeader();
extern int DAT_0052f620[4];
int **igMemoryPool_CopyConstruct(int **arg0) {
    igObject_CopyConstructHeader();
    *arg0 = &DAT_0052f620[0];
    return arg0;
}
