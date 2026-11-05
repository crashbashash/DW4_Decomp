/* 0x00187dd0 — FUN_00187dd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00187c70();
extern int DAT_00560f90[4];
int FUN_00187dd0(void) {
    if (DAT_00560f90[0] == 0) {
        FUN_00187c70();
    }
    return DAT_00560f90[0];
}
