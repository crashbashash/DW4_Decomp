/* 0x0025d270 — FUN_0025d270. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025d078();
int FUN_0025d0b8();
extern int DAT_00498c5c[4];
extern int DAT_004ed7f8[4];
int FUN_0025d270(int arg0, int arg1, int arg2) {
    if (DAT_00498c5c[0] == 0) {
        FUN_0025d078();
    }
    FUN_0025d0b8(&DAT_004ed7f8[0], 6, arg0, arg1, arg2);
    return 0;
}
