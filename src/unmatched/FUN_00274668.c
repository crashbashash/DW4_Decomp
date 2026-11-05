/* 0x00274668 — FUN_00274668. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
char FUN_00274668(char arg0) {
    char temp_v1;
    char var_a0;

    var_a0 = arg0;
    temp_v1 = var_a0;
    if ((unsigned int) (var_a0 - 0x61) < 0x1AU) {
        var_a0 -= 0x20;
    }
    return ((temp_v1 ^ 0x5C) != 0) ? var_a0 : 0x2F;
}
