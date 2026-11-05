/* 0x00281898 — FUN_00281898. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00281a00();
extern int DAT_00570c00[4];
void FUN_00281898(int *arg0, int *arg1, int *arg2, int *arg3) {
    FUN_00281a00(0xFD00, 0, 0, 0x10);
    *arg0 = *(int *)((char *)&(DAT_00570c00[0]) + 0);
    *arg1 = *(int *)((char *)&(DAT_00570c00[0]) + 4);
    *arg2 = *(int *)((char *)&(DAT_00570c00[0]) + 8);
    *arg3 = *(int *)((char *)&(DAT_00570c00[0]) + 12);
}
