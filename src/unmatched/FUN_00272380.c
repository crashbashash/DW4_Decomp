/* 0x00272380 — FUN_00272380. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00116c80();
int FUN_002725a0();

int FUN_00272380(void) {
    int temp_s0;

    FUN_002725a0(0x2300);
    temp_s0 = FUN_00116c80(1);
    FUN_002725a0(0x2301);
    return temp_s0;
}
