/* 0x001b6be0 — FUN_001b6be0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00130830();
int FUN_00130a70();
int FUN_00130cf0();
int FUN_001318f0();
int FUN_00132a00();
int FUN_001357e0();
int FUN_0013b110();
int FUN_0019a6e0(int);
int Memory_GetAllocatorBySelector(int);

void FUN_001b6be0(void) {
    *(int *)0x562640 = FUN_0019a6e0(Memory_GetAllocatorBySelector(*(int *)0x587038));
    FUN_0013b110();
    FUN_00132a00();
    FUN_001357e0();
    FUN_00130cf0();
    FUN_001318f0();
    FUN_00130830();
    FUN_00130a70();
}
