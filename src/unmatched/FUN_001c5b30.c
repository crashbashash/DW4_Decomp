/* 0x001c5b30 — FUN_001c5b30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001c59e0();
int FUN_001c59f0(int, int, int, int);

void FUN_001c5b30(int arg0, int arg1, int arg2) {
    FUN_001c59f0(arg0, FUN_001c59e0(), arg1, arg2);
}
