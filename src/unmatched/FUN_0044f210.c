int igMetaObject_Create();
int Memory_GetAllocatorBySelector();
extern int DAT_00587040[4];
extern int DAT_0058c3c8[4];
int FUN_0044f210(void) {
    if (DAT_0058c3c8[0] == 0) {
        DAT_0058c3c8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c3c8[0];
}
