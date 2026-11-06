int igMetaObject_Create();
int Memory_GetAllocatorBySelector();
extern int DAT_0056d8b8[4];
extern int DAT_00587040[4];
int FUN_00226340(void) {
    if (DAT_0056d8b8[0] == 0) {
        DAT_0056d8b8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056d8b8[0];
}
