/* 0x00292958 — FUN_00292958. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00294ef8();
int FUN_0029a320();
int FUN_002abd18();
extern int DAT_004f2d48[4];
void FUN_00292958(void) {
    if (FUN_002abd18() != 0) {
        FUN_00294ef8(-0x132);
        FUN_0029a320(&DAT_004f2d48[0]);
    }
}
