int Memory_GetAllocatorBySelector();
int igMetaObject_Create();
extern int DAT_00587040[4];
extern int DAT_0058c700[4];
int FUN_00458ae0(void) {
    if (DAT_0058c700[0] == 0) {
        DAT_0058c700[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c700[0];
}
