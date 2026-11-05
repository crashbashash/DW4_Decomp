/* 0x0029aa10 — FUN_0029aa10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002648e8();
int FUN_0029aa78();
int FUN_0029ac78();

int FUN_0029aa10(int arg0) {
    int temp_v0;
    int var_s2;

    var_s2 = 0;
    temp_v0 = FUN_002648e8();
    if ((temp_v0 == 1) && (FUN_0029aa78() != temp_v0)) {
        var_s2 = FUN_0029ac78(arg0);
    }
    return var_s2;
}
