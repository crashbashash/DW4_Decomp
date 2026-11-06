int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_005614a8[4];
extern int DAT_00587040[4];
int FUN_001983e0(void) {
    if (DAT_005614a8[0] == 0) {
        DAT_005614a8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005614a8[0];
}
