/* 0x00270478 — FUN_00270478. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026f530();
extern int DAT_004ef388[4];
int FUN_00270478(void *arg0) {
    int (*temp_v0)(int, int, int, int);
    int var_v1;

    if (arg0 == 0) {
        FUN_0026f530(&DAT_004ef388[0]);
        return -1;
    }
    temp_v0 = (int (*)(int, int, int, int))(*(int *)((char *)(*(int *)((char *)(arg0) + 0)) + 96));
    var_v1 = 0x7FFFFFFF;
    if (temp_v0 != 0) {
        var_v1 = (int)(temp_v0(*(int *)((char *)(arg0) + 4), 0x12C, 0, 0));
    }
    return var_v1;
}
