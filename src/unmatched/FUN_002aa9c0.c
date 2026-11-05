/* 0x002aa9c0 — FUN_002aa9c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002aa9c0(void *arg0) {
    int temp_v1;
    int var_a1;

    temp_v1 = *(int *)((char *)(arg0) + 76);
    var_a1 = *(int *)((char *)(arg0) + 72);
    if ((temp_v1 >= 2) && ((temp_v1 < 5) || (temp_v1 == 6))) {
        var_a1 = 2;
    }
    return var_a1;
}
