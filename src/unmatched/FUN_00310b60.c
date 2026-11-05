/* 0x00310b60 — FUN_00310b60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002f8870();
int FUN_003081d0();
int FUN_003105c0();
extern int DAT_004fb620[4];
extern int DAT_004fbae0[4];
extern unsigned char DAT_00554cb0[4];
void FUN_00310b60(void *arg0, unsigned char *arg1) {
    int temp_a0;
    int temp_v0;

    FUN_003105c0();
    if (*(int *)((char *)arg0 + 184) > 0) {
        temp_a0 = *(int *)((char *)arg0 + 188);
        if ((temp_a0 > 0) && !(*arg1 & 1) && (temp_a0 > 0)) {
            FUN_002f8870(0, arg0);
            if (DAT_00554cb0[0] == 0) {
                temp_v0 = FUN_003081d0(&DAT_004fb620[0], arg1, &DAT_004fbae0[0]);
                if ((temp_v0 != 1) && (temp_v0 == 2)) {
                    DAT_00554cb0[0] = 1;
                }
            }
        }
    }
}
