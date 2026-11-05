/* 0x002726f8 — FUN_002726f8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004a92c4[];
int FUN_00117870();
int FUN_00117940();
int FUN_002725a0();
int FUN_0027eca8();

int FUN_002726f8(int arg0) {
    int temp_s0;
    int var_s1;
    int var_v0;

    var_v0 = FUN_0027eca8(DAT_004a92c4);
    var_s1 = 0;
    if (var_v0 != 0) {
        FUN_002725a0(0x9600);
        temp_s0 = FUN_00117870(arg0);
        FUN_002725a0(0x9601);
        if (temp_s0 == 0) {
            var_s1 = FUN_00117940();
        }
        *(int *)DAT_004a92c4 = 0;
        var_v0 = var_s1;
    }
    return var_v0;
}
