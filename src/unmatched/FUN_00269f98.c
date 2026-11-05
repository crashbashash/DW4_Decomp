/* 0x00269f98 — FUN_00269f98. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026a0e0();
int FUN_0026a2a0();
int memset();

void FUN_00269f98(char *arg0) {
    if (arg0 != 0) {
        FUN_0026a2a0();
        FUN_0026a0e0(arg0);
        *arg0 = 0;
        memset(arg0, 0, 0x60);
    }
}
