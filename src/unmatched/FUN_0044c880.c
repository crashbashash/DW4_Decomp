int igMetaObject_Create();
int Memory_GetAllocatorBySelector();
extern int DAT_00587040[4];
extern int DAT_0058c218[4];
int FUN_0044c880(void) {
    if (DAT_0058c218[0] == 0) {
        DAT_0058c218[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c218[0];
}
