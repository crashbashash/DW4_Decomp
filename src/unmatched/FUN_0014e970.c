/* 0x0014e970 — FUN_0014e970. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_Create();
int Memory_GetAllocatorBySelector();
extern int DAT_0055fe48[4];
extern int DAT_00587040[4];
int FUN_0014e970(void) {
    if (DAT_0055fe48[0] == 0) {
        DAT_0055fe48[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055fe48[0];
}
