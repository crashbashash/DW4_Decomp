/* 0x00272970 — FUN_00272970. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0010d108();
int FUN_0010f970();
int FUN_00272688();
int FUN_002726c0();
extern int DAT_004eff00[4];
int FUN_00272970(int arg0, int arg1, int arg2) {
    int temp_v0;

    FUN_00272688();
    temp_v0 = FUN_0010f970(arg0, arg1, arg2);
    if (temp_v0 < 0) {
        FUN_0010d108(&DAT_004eff00[0], temp_v0);
    }
    FUN_002726c0();
    return temp_v0;
}
