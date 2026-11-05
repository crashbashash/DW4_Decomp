/* 0x00294c10 — FUN_00294c10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029a0a0();
int FUN_0029a100();
int FUN_0029a150();
int FUN_0029a1a0();
int FUN_0029a948();
int FUN_0029a990();
int FUN_0029aa10();

void FUN_00294c10(void) {
    FUN_0029a0a0(2, &FUN_0029a948, 0);
    FUN_0029a150(&FUN_0029a990, 0);
    FUN_0029a100(&FUN_0029aa10, 0);
    FUN_0029a1a0();
}
