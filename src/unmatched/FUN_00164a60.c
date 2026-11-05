/* 0x00164a60 — FUN_00164a60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00554b24[4];
extern int DAT_00560688[4];
extern int DAT_0056068c[4];
extern int DAT_00561098[4];
extern int DAT_00586858[4];
int *FUN_00164a60(void) {
    if (DAT_00554b24[0] == 0) {
        DAT_00554b24[0] = 1;
        DAT_00560688[0] = DAT_00586858[0];
        DAT_0056068c[0] = DAT_00561098[0];
    }
    return &DAT_00560688[0];
}
