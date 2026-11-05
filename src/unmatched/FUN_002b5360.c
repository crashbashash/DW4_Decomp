/* 0x002b5360 — FUN_002b5360. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0012aba0();
extern int DAT_004f5a40[4];
int FUN_002b5360(int arg0, int arg1) {
    if ((arg0 == 0) || (arg1 < 0)) {
        return 0;
    }
    return FUN_0012aba0(arg0 + 0x13, &DAT_004f5a40[0], 1) == 0;
}
