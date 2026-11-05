/* 0x0019e640 — FUN_0019e640. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001ce710();
int FUN_002fe490();
void FUN_001ce660(void);  /* code at 0x1ce660, passed by address (was DAT_1ce660; docs/engine/function-inventory.md) */
void FUN_0019e640(void) {
    FUN_001ce710();
    FUN_002fe490(FUN_001ce660);
}
