/* 0x002914b0 — FUN_002914b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002852a0();

void FUN_002914b0(void *arg0) {
    int var_v0;

    var_v0 = 0;
    if (arg0 != 0) {
        var_v0 = *(int *)((char *)(arg0) + 944);
    }
    FUN_002852a0(var_v0);
}
