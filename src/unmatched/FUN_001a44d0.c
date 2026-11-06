/* The second call passes the address of FUN_001b68b0, a 16-byte wrapper that loads a global and
 * tail-calls FUN_001b68c0. Ghidra had folded that wrapper into FUN_001b4c40's extent and named the
 * address DAT_001b68b0; the symbol table now carries it as a function (config/SLUS-20836/extent-
 * overrides.tsv, `cut` row for FUN_001b4c40). */
int FUN_001b6be0();
int FUN_002fe490(void (*)(void));
void FUN_001b68b0(void);
void FUN_001a44d0(void) {
    FUN_001b6be0();
    FUN_002fe490(FUN_001b68b0);
}
