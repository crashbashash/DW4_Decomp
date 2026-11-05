int Memory_GetAllocatorBySelector();
int igMetaObject_Create();
extern int DAT_00587040[4];
extern int DAT_0058cda0[4];
int FUN_0045d830(void) {
    if (DAT_0058cda0[0] == 0) {
        DAT_0058cda0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058cda0[0];
}
