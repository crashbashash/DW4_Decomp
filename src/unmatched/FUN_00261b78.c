/* 0x00261b78 — FUN_00261b78. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00260c20();
int FUN_00261778();
int FUN_00261aa0();
int FUN_00261c88();

int FUN_00261b78(int arg0, int arg1) {
    int temp_a0;
    int var_s0;

    FUN_00260c20(2, 0, arg0, arg1, -1);
    var_s0 = FUN_00261778();
    if (var_s0 != 0) {
        if (FUN_00261aa0(var_s0, arg0, arg1) < 0) {
            temp_a0 = var_s0;
            var_s0 = 0;
            FUN_00261c88(temp_a0);
        }
    }
    FUN_00260c20(2, 1, arg0, arg1, -1);
    return var_s0;
}
