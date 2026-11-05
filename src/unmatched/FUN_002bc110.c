/* 0x002bc110 — FUN_002bc110. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00585aa8[4];
extern int DAT_00587040[4];
int FUN_002bc110(void) {
    if (DAT_00585aa8[0] == 0) {
        DAT_00585aa8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00585aa8[0];
}
