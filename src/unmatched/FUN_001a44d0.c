/* 0x001a44d0 — FUN_001a44d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 *
 * The second call passes the address of FUN_001b68b0, a 16-byte wrapper that
 * loads a global and tail-calls FUN_001b68c0. Ghidra had folded that wrapper
 * into FUN_001b4c40's extent and named the address DAT_001b68b0; the symbol
 * table now carries it as a function (config/SLUS-20836/extent-overrides.tsv, `cut` row
 * for FUN_001b4c40; docs/engine/function-inventory.md). */
int FUN_001b6be0();
int FUN_002fe490(void (*)(void));
void FUN_001b68b0(void);
void FUN_001a44d0(void) {
    FUN_001b6be0();
    FUN_002fe490(FUN_001b68b0);
}
