/* 0x001eb3f0 — FUN_001eb3f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00562dac[];
int FUN_001eb3f0(int arg0) {
    return *(int *)(DAT_00562dac + (arg0 << 6)) & 1;
}
