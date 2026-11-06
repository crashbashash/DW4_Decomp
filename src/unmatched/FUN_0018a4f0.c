int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_005610d8[4];
extern int DAT_00587040[4];
int FUN_0018a4f0(void) {
    if (DAT_005610d8[0] == 0) {
        DAT_005610d8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005610d8[0];
}
