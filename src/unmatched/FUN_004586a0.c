int Memory_GetAllocatorBySelector();
int igMetaObject_Create();
extern int DAT_00587040[4];
extern int DAT_0058c680[4];
int FUN_004586a0(void) {
    if (DAT_0058c680[0] == 0) {
        DAT_0058c680[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c680[0];
}
