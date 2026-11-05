/* 0x00285a90 — FUN_00285a90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002855d8();
int FUN_00285b10();
int FUN_00285c78();
int FUN_0028b098();

int FUN_00285a90(int arg0, int arg1) {
    int temp_v0;

    if (FUN_0028b098() != 0) {
        return FUN_002855d8(0, 0xFF03020C);
    }
    temp_v0 = FUN_00285c78(arg0, arg1);
    if (temp_v0 == 0) {
        FUN_00285b10(arg0);
    }
    return temp_v0;
}
