/* 0x00229f90 — FUN_00229f90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00229f90(int *arg0, int *arg1) {
    return (unsigned int) (*arg0 - 8) < (unsigned int) (*arg1 - 8);
}
