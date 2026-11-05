/* 0x00125fa8 — FUN_00125fa8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00125f70();
extern int DAT_004854a0[4];
void FUN_00125fa8(void) {
    FUN_00125f70(DAT_004854a0[0]);
}
