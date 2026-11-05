/* 0x001eeed0 — FUN_001eeed0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memcpy(int, int, int);
int FUN_00330730(int, int);

int FUN_001eeed0(int arg0) {
    int temp_v0;

    temp_v0 = FUN_00330730(0x38, 0xB);
    memcpy(temp_v0, arg0, 0x38);
    return temp_v0;
}
