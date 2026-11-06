int igMetaObject_Create();
int Memory_GetAllocatorBySelector();
extern int DAT_0056dae0[4];
extern int DAT_00587040[4];
int FUN_00231790(void) {
    if (DAT_0056dae0[0] == 0) {
        DAT_0056dae0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dae0[0];
}
