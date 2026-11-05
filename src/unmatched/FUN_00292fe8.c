/* 0x00292fe8 — FUN_00292fe8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029a320();
extern int DAT_004f2f58[4];
extern int DAT_004f2f88[4];
int FUN_00292fe8(void *arg0) {
    int var_a0;

    var_a0 = 1;
    if (*(int *)((char *)(arg0) + 0) == 2) {
        FUN_0029a320(&DAT_004f2f58[0]);
        var_a0 = 0;
    }
    if ((unsigned int) *(int *)((char *)(arg0) + 36) >= 3U) {
        FUN_0029a320(&DAT_004f2f88[0]);
        var_a0 = 0;
    }
    return var_a0;
}
