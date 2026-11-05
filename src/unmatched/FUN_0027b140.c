/* 0x0027b140 — FUN_0027b140. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002659a0();
extern int DAT_004b1dc0[4];
extern int DAT_004b1dc8[4];
extern int DAT_004f1a00[4];
void FUN_0027b140(void) {
    if ((DAT_004b1dc8[0] != 1) || (DAT_004b1dc0[0] > 0)) {
        FUN_002659a0(&DAT_004f1a00[0]);
    }
}
