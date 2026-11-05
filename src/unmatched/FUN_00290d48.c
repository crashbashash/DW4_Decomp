/* 0x00290d48 — FUN_00290d48. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00573f5c[4];
int FUN_00290d48(int arg0) {
    int var_a0;

    var_a0 = arg0;
    if (DAT_00573f5c[0] != 0) {
        var_a0 |= 0x02000000;
    }
    return var_a0;
}
