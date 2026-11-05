/* 0x001ddfd0 — FUN_001ddfd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002d4c20(int, int, int);
int igMetaObject_FindFieldByName(int, int *);
extern int DAT_004e13a0[4];
extern int DAT_005611d8[4];
void FUN_001ddfd0(void) {
    int temp_v0;

    if (DAT_005611d8[0] != 0) {
        temp_v0 = igMetaObject_FindFieldByName(DAT_005611d8[0], &DAT_004e13a0[0]);
        if (temp_v0 != 0) {
            FUN_002d4c20(temp_v0, 0, 1);
            FUN_002d4c20(temp_v0, 1, 3);
            FUN_002d4c20(temp_v0, 2, 1);
        }
    }
}
