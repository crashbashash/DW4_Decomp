/* 0x002b6330 — FUN_002b6330. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b61d0();
extern int DAT_005856f0[4];
int FUN_002b6330(void) {
    if (DAT_005856f0[0] == 0) {
        FUN_002b61d0();
    }
    return DAT_005856f0[0];
}
