/* 0x00463b70 — FUN_00463b70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00236e80(int);
int FUN_00237280(int);
int FUN_002376b0(int);

void FUN_00463b70(int *arg0) {
    FUN_00237280(*arg0);
    FUN_00236e80(*arg0);
    FUN_002376b0(*arg0);
}
