extern "C" {
/* 0x0033e310 — FUN_0033e310. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObject_InitHeader();
extern int DAT_005338a0[4];
int **FUN_0033e310(int **arg0) {
    igObject_InitHeader();
    *arg0 = &DAT_005338a0[0];
    return arg0;
}
}
