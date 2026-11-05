/* 0x00273218 — FUN_00273218. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004aa3b0[];
int FUN_0010e2a8();
extern int DAT_0056e580[4];
extern int DAT_0056e680[4];
void FUN_00273218(int arg0) {
    DAT_0056e580[0] = arg0;
    FUN_0010e2a8(DAT_004aa3b0, 3, 0, &DAT_0056e580[0], 4, &DAT_0056e680[0], 0, 0, 0);
}
