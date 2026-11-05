/* 0x002ca8f0 — FUN_002ca8f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00586878[4];
extern int DAT_00587040[4];
int FUN_002ca8f0(void) {
    if (DAT_00586878[0] == 0) {
        DAT_00586878[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00586878[0];
}
