/* 0x001a6600 — FUN_001a6600. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_005620c8[4];
extern int DAT_00587040[4];
int FUN_001a6600(void) {
    if (DAT_005620c8[0] == 0) {
        DAT_005620c8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005620c8[0];
}
