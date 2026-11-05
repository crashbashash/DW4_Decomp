/* 0x00233480 — FUN_00233480. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_Create();
int Memory_GetAllocatorBySelector();
extern int DAT_0056dc28[4];
extern int DAT_00587040[4];
int FUN_00233480(void) {
    if (DAT_0056dc28[0] == 0) {
        DAT_0056dc28[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dc28[0];
}
