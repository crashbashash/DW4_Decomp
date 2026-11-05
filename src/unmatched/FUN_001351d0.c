/* 0x001351d0 — FUN_001351d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_Create();
int Memory_GetAllocatorBySelector();
extern int DAT_0055efd0[4];
extern int DAT_00587040[4];
int FUN_001351d0(void) {
    if (DAT_0055efd0[0] == 0) {
        DAT_0055efd0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055efd0[0];
}
