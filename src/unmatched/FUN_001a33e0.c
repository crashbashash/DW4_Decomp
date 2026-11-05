/* 0x001a33e0 — FUN_001a33e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001bb200();
int FUN_002fe490();
void FUN_001bb1f0(void);  /* code at 0x1bb1f0, passed by address (was DAT_1bb1f0; docs/engine/function-inventory.md) */
void FUN_001a33e0(void) {
    FUN_001bb200();
    FUN_002fe490(FUN_001bb1f0);
}
