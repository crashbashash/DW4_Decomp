/* 0x00271970 — FUN_00271970. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00116c80();
int FUN_002725a0();

void FUN_00271970(void) {
    FUN_002725a0(0x1300);
    FUN_00116c80(0);
    FUN_002725a0(0x1301);
}
