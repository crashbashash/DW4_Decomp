/* 0x002adec8 — FUN_002adec8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002adf48();

int FUN_002adec8(int arg0, int arg1, int arg2) {
    if (FUN_002a0dd8() != 0) {
        return FUN_002a0bb8(0, 0xFF000117, arg2);
    }
    FUN_002adf48(arg0, arg1, arg2);
    return 0;
}
