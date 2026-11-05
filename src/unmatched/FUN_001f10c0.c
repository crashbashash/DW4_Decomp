/* 0x001f10c0 — FUN_001f10c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_005692c0[];
void FUN_001f10c0(int arg0, int arg1) {
    *(int *)(DAT_005692c0 + (arg0 * 4)) = arg1;
}
