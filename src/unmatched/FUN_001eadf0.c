/* 0x001eadf0 — FUN_001eadf0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00562dc0[];
int FUN_001eadf0(int arg0) {
    return *(int *)(DAT_00562dc0 + (arg0 << 6));
}
