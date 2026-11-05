/* 0x0022b400 — FUN_0022b400. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0012fce0();

int FUN_0022b400(void *arg0, int arg1, int arg2) {
    int var_v0;

    var_v0 = -1;
    if (*(unsigned char *)((char *)(arg0) + 32) != 0) {
        var_v0 = FUN_0012fce0(arg1, arg2);
    }
    return var_v0;
}
