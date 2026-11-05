/* 0x0032f260 — FUN_0032f260. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00328de0();
extern int DAT_0052d8b0[4];
int **FUN_0032f260(int **arg0) {
    FUN_00328de0();
    *arg0 = &DAT_0052d8b0[0];
    return arg0;
}
