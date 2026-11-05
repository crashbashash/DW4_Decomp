/* 0x0032ae00 — FUN_0032ae00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0032ac70();

void FUN_0032ae00(int arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_s2;

    var_s2 = 0;
    do {
        temp_v1 = FUN_0032ac70(arg0, var_s2) * 4;
        var_s2 += 1;
        temp_a1 = (int *)(arg1 + temp_v1);
        *temp_a1 += 1;
    } while (var_s2 < 0x4000);
}
