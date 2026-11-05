/* 0x001f76c0 — FUN_001f76c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001f76f0(int, int *);

void FUN_001f76c0(int arg0) {
    int sp1C;

    sp1C = arg0;
    FUN_001f76f0(1, &sp1C);
}
