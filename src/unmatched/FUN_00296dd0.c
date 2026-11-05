/* 0x00296dd0 — FUN_00296dd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a3200();

void FUN_00296dd0(void *arg0, int arg1) {
    int var_v0;

    var_v0 = 0;
    if (arg0 != 0) {
        var_v0 = *(int *)((char *)(arg0) + 64);
    }
    FUN_002a3200(var_v0, 3, arg1);
}
