/* 0x0010b6b8 — FUN_0010b6b8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001145c8(int);

int FUN_0010b6b8(int arg0, int arg1) {
    if (arg0 == 1) {
        FUN_001145c8(arg1);
    }
    return 0;
}
