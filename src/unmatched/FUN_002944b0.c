/* 0x002944b0 — FUN_002944b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00294938();

int FUN_002944b0(void) {
    int var_v1;

    var_v1 = FUN_00294938();
    if ((var_v1 == 0x51) || (var_v1 == 0x61)) {
        var_v1 = 0x41;
    }
    return var_v1;
}
