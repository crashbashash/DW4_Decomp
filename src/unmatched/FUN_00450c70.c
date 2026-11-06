int igMetaObject_Create();
int Memory_GetAllocatorBySelector();
extern int DAT_00587040[4];
extern int DAT_0058c548[4];
int FUN_00450c70(void) {
    if (DAT_0058c548[0] == 0) {
        DAT_0058c548[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c548[0];
}
