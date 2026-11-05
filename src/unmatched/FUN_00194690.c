/* 0x00194690 — FUN_00194690. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001e0410();
int FUN_002fe490(int *);
void FUN_001e02e0(void);  /* code at 0x1e02e0, passed by address (was DAT_1e02e0; docs/engine/function-inventory.md) */
void FUN_00194690(void) {
    FUN_001e0410();
    FUN_002fe490((int *)FUN_001e02e0);
}
