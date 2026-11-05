/* 0x0025d078 — FUN_0025d078. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00498c5c[];
int FUN_0025d078(void) {
    *(int *)DAT_00498c5c += 1;
    return 0;
}
