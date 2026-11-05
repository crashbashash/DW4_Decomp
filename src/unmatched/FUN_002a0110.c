/* 0x002a0110 — FUN_002a0110. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a0150();
int FUN_002a0288();

void FUN_002a0110(int arg0) {
    int temp_v0;

    temp_v0 = FUN_002a0288();
    if (temp_v0 != 0) {
        FUN_002a0150(temp_v0, arg0 + 0x78);
    }
}
