/* 0x00197e60 — FUN_00197e60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00561488[4];
extern int DAT_00587040[4];
int FUN_00197e60(void) {
    if (DAT_00561488[0] == 0) {
        DAT_00561488[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00561488[0];
}
