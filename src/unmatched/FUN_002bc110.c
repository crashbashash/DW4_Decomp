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
