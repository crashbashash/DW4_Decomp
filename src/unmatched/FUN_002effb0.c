/* 0x002effb0 — FUN_002effb0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObject_ConstructHeader();
extern int DAT_0052f620[4];
int **FUN_002effb0(int **arg0) {
    igObject_ConstructHeader();
    *arg0 = &DAT_0052f620[0];
    return arg0;
}
