/* 0x00276350 — FUN_00276350. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00276338();

int FUN_00276350(char arg0, char arg1) {
    int temp_s0;

    temp_s0 = FUN_00276338(arg0);
    return ((temp_s0 ^ FUN_00276338(arg1)) != 0) ? -1 : 0;
}
