/* 0x00463b30 — FUN_00463b30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00236ca0(int);
int FUN_002371f0(int);
int FUN_00237530(int);

void FUN_00463b30(int *arg0) {
    FUN_00237530(*arg0);
    FUN_00236ca0(*arg0);
    FUN_002371f0(*arg0);
}
