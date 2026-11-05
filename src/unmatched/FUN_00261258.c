/* 0x00261258 — FUN_00261258. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_0049a758[];
int FUN_00261218();
int FUN_00262118();
int FUN_00262678();
extern int DAT_0049a75c[4];
void FUN_00261258(void) {
    int temp_a0;

    temp_a0 = *(int *)DAT_0049a758;
    if ((temp_a0 != 0) && (DAT_0049a75c[0] >= 0)) {
        if (FUN_00262678(temp_a0) != 1) {
            FUN_00262118(*(int *)DAT_0049a758);
        }
        FUN_00261218();
    }
}
