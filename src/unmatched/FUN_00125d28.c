/* 0x00125d28 — FUN_00125d28. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00125d78();
extern int DAT_004854a0[4];
void FUN_00125d28(int arg0, int arg1) {
    FUN_00125d78(DAT_004854a0[0], arg0, arg1);
}
