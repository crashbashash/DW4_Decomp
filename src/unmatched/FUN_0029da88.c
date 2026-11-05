/* 0x0029da88 — FUN_0029da88. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0029da88(void *arg0) {
    int var_v0;
    void *var_a0;

    var_a0 = (void *)(arg0);
    var_v0 = 2;
    do {
        var_v0 -= 1;
        *(int *)((char *)(var_a0) + 0) = 0;
        *(int *)((char *)(var_a0) + 4) = 0;
        *(int *)((char *)(var_a0) + 8) = 0;
        *(int *)((char *)(var_a0) + 12) = 0;
        var_a0 = (void *)((char *)var_a0 + (0x10));
    } while (var_v0 >= 0);
}
