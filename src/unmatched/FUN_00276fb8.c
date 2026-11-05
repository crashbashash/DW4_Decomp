/* 0x00276fb8 — FUN_00276fb8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00277278();
int memset();

void FUN_00276fb8(char *arg0) {
    if (arg0 != 0) {
        FUN_00277278();
        *arg0 = 0;
        memset(arg0, 0, 0x238);
    }
}
