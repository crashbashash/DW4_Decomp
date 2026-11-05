/* 0x001d9740 — FUN_001d9740. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001e04c0(int, int);

int FUN_001d9740(void *arg0, int arg1) {
    int temp_v1;
    int var_v0;

    temp_v1 = *(int *)((char *)arg0 + 12);
    var_v0 = 0;
    if (temp_v1 != 0) {
        var_v0 = FUN_001e04c0(arg1, temp_v1);
    }
    return var_v0;
}
