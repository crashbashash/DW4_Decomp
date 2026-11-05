/* 0x001bbae0 — FUN_001bbae0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001bbb30(int, int);
int FUN_001bc050(int, int, int);

void FUN_001bbae0(int arg0, int arg1) {
    FUN_001bc050(FUN_001bbb30(arg1, arg0), arg1, arg0);
}
