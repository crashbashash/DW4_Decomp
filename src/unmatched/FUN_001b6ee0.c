/* 0x001b6ee0 — FUN_001b6ee0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int Matrix44_Copy(int);
int FUN_00191f30(int *, int, int);

void FUN_001b6ee0(int arg0, int arg1) {
    int sp3C;

    Matrix44_Copy(arg0 + 0x64);
    FUN_00191f30(&sp3C, arg0 + 0xA4, arg1);
}
