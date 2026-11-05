/* 0x002715e0 — FUN_002715e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026f530();
extern int DAT_004efb60[4];
int FUN_002715e0(void *arg0) {
    int (*temp_v0)(int, int, int, int);
    int var_v1;

    var_v1 = 0;
    if (arg0 == 0) {
        FUN_0026f530(&DAT_004efb60[0]);
        return 0;
    }
    temp_v0 = (int (*)(int, int, int, int))(*(int *)((char *)(*(int *)((char *)(arg0) + 0)) + 96));
    if (temp_v0 != 0) {
        var_v1 = (int)(temp_v0(*(int *)((char *)(arg0) + 4), 0x12B, 0, 0));
    }
    return var_v1;
}
