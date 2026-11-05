/* 0x002c8980 — FUN_002c8980. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_005867b8[4];
extern int DAT_00587040[4];
int FUN_002c8980(void) {
    if (DAT_005867b8[0] == 0) {
        DAT_005867b8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005867b8[0];
}
