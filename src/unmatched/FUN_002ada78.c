/* 0x002ada78 — FUN_002ada78. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002adb18();

void FUN_002ada78(int arg0, int arg1, int arg2) {
    if (FUN_002adb18() != 0) {
        *(int *)((char *)(((arg1 * 4) + arg0)) + 2564) = arg2;
    }
}
