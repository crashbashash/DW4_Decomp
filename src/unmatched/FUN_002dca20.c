/* 0x002dca20 — FUN_002dca20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c5e10();
int Memory_GetAllocatorBySelector();
extern unsigned char DAT_00554bfc[4];
extern int DAT_00586590[4];
extern int DAT_00586df8[4];
extern int DAT_00587038[4];
int FUN_002dca20(void) {
    if ((DAT_00586df8[0] == 0) && (DAT_00586590[0] != 0) && (DAT_00554bfc[0] == 0)) {
        DAT_00586df8[0] = FUN_002c5e10(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    }
    return DAT_00586df8[0];
}
