/* 0x00275458 — FUN_00275458. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002725a0();
int FUN_00272838();

int FUN_00275458(void *arg0) {
    int temp_s0;
    int var_v0;

    FUN_002725a0(0x4000);
    temp_s0 = FUN_00272838(*(int *)((char *)(arg0) + 24), 1, (char *)arg0 + 0x14);
    FUN_002725a0(0x4001);
    var_v0 = 0;
    if (temp_s0 >= 0) {
        var_v0 = *(int *)((char *)(arg0) + 20) != 1;
    }
    return var_v0;
}
