/* 0x00123730 — FUN_00123730. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00123798();
int FUN_00127310();
int FUN_00127390();
extern int DAT_004854a0[4];
int FUN_00123730(int arg0, int arg1) {
    int temp_s1;

    FUN_00127310(DAT_004854a0[0]);
    temp_s1 = FUN_00123798(DAT_004854a0[0], arg0, arg1);
    FUN_00127390(DAT_004854a0[0]);
    return temp_s1;
}
