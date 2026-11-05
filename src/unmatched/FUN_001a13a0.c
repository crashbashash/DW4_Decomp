/* 0x001a13a0 — FUN_001a13a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001c45a0();
int FUN_002fe490(int *);
void FUN_001c4590(void);  /* code at 0x1c4590, passed by address (was DAT_1c4590; docs/engine/function-inventory.md) */
void FUN_001a13a0(void) {
    FUN_001c45a0();
    FUN_002fe490((int *)FUN_001c4590);
}
