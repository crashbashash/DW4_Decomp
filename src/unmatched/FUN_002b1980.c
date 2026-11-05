/* 0x002b1980 — FUN_002b1980. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b19c8();

int FUN_002b1980(void *arg0) {
    int temp_v0;
    int var_v0;

    var_v0 = FUN_002b19c8();
    if ((var_v0 != 0) && ((temp_v0 = *(int *)((char *)(arg0) + 12), (temp_v0 == 0x6B)) || (var_v0 = 0, ((temp_v0 < 0x6E) == 0)))) {
        var_v0 = 1;
    }
    return var_v0;
}
