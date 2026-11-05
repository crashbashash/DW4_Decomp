/* 0x001eae10 — FUN_001eae10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00562da0[];
extern char DAT_00562db8[];
extern char DAT_00562dbc[];
extern char DAT_00562dc8[];
void FUN_001eae10(int arg0, int arg1) {
    int temp_a2;

    temp_a2 = arg0 << 6;
    *(int *)(DAT_00562db8 + temp_a2) = (int) ((arg1 << 6) + DAT_00562da0);
    *(int *)(DAT_00562dbc + temp_a2) = 0;
    *(int *)(DAT_00562dc8 + temp_a2) = (int) (*(int *)(DAT_00562dc8 + temp_a2) | 2);
}
