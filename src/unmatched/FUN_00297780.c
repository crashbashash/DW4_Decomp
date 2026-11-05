/* 0x00297780 — FUN_00297780. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b3788();
int FUN_002b38b0();
int FUN_002977a8();

void FUN_00297780(void) {
    FUN_002b3788();
    FUN_002b38b0(&FUN_002977a8, 0);
}
