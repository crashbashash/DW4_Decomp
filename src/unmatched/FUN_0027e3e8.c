/* 0x0027e3e8 — FUN_0027e3e8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0012a9f0();
int strncpy();
extern int DAT_004bb040[4];
extern int DAT_00570bb0[4];
void FUN_0027e3e8(int arg0, int arg1) {
    strncpy(&DAT_004bb040[0], arg0, 0x7F);
    FUN_0012a9f0(&DAT_004bb040[0], arg1, 0x7F);
    if (*(int *)((char *)&(DAT_00570bb0[0]) + 0) != 0) {
        ((int (*)())*(int *)((char *)&(DAT_00570bb0[0]) + 0))(*(int *)((char *)&(DAT_00570bb0[0]) + 4), &DAT_004bb040[0]);
    }
}
