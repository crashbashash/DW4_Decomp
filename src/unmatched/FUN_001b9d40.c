/* 0x001b9d40 — FUN_001b9d40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001b7f50(int, int);
int FUN_001b85c0(int, int, int);

void FUN_001b9d40(int arg0, int arg1) {
    FUN_001b85c0(FUN_001b7f50(arg1, arg0), arg1, arg0);
}
