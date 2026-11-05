/* 0x002a39b8 — FUN_002a39b8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a3a18();
int FUN_002a3a60();
int FUN_002a84e0();

int FUN_002a39b8(int arg0) {
    if ((FUN_002a84e0() != 0) || ((FUN_002a3a18(arg0) != 0) && (FUN_002a3a60(arg0) != 0))) {
        return 1;
    }
    return 0;
}
