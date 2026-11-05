/* 0x001e68a0 — FUN_001e68a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001e6770(int);
int FUN_001e6820(int, int);

int FUN_001e68a0(int arg0, int arg1) {
    FUN_001e6820(arg0, FUN_001e6770(arg1));
    return 1;
}
