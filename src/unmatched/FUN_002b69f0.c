/* 0x002b69f0 — FUN_002b69f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b6890();
extern int DAT_00585718[4];
int FUN_002b69f0(void) {
    if (DAT_00585718[0] == 0) {
        FUN_002b6890();
    }
    return DAT_00585718[0];
}
