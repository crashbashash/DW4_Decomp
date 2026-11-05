/* 0x00261218 — FUN_00261218. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00261c88();
extern int DAT_0049a754[4];
extern int DAT_0049a758[4];
extern int DAT_0049a76c[4];
void FUN_00261218(void) {
    FUN_00261c88(DAT_0049a758[0]);
    DAT_0049a758[0] = 0;
    DAT_0049a754[0] = 0;
    DAT_0049a76c[0] = 0;
}
