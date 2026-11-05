/* 0x00280a70 — FUN_00280a70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int **FUN_00126308();
extern int DAT_0052d710[4];
extern int DAT_0052d730[4];
void FUN_00280a70(int ***arg0, int **arg1) {
    int **temp_v0;

    if (arg1 != 0) {
        *arg0 = arg1;
        return;
    }
    temp_v0 = FUN_00126308(4);
    if (temp_v0 != 0) {
        *temp_v0 = &DAT_0052d730[0];
        *temp_v0 = &DAT_0052d710[0];
    }
    *arg0 = temp_v0;
}
