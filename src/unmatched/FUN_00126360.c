/* 0x00126360 — FUN_00126360. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001253e8();
int FUN_00127310();
int FUN_00127390();
extern int DAT_004854a0[4];
void FUN_00126360(int arg0) {
    FUN_00127310(DAT_004854a0[0]);
    FUN_001253e8(DAT_004854a0[0], arg0);
    FUN_00127390(DAT_004854a0[0]);
}
