/* 0x0030d050 — FUN_0030d050. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0030d0d0(int *, int, int);

void FUN_0030d050(int arg0) {
    int sp1C;

    FUN_0030d0d0(&sp1C, arg0, 0);
}
