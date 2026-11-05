/* 0x0028af38 — FUN_0028af38. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002855d8();
int FUN_0028b098();

void FUN_0028af38(int *arg0) {
    if (FUN_0028b098() != 0) {
        FUN_002855d8(0, 0xFF030201);
        return;
    }
    *arg0 = 1;
}
