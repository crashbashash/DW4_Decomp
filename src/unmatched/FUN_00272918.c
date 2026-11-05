/* 0x00272918 — FUN_00272918. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0010d108();
int FUN_0010f5b8();
int FUN_00272688();
int FUN_002726c0();
extern int DAT_004efee0[4];
int FUN_00272918(int arg0) {
    int temp_v0;

    FUN_00272688();
    temp_v0 = FUN_0010f5b8(arg0);
    if (temp_v0 < 0) {
        FUN_0010d108(&DAT_004efee0[0], temp_v0);
    }
    FUN_002726c0();
    return temp_v0;
}
