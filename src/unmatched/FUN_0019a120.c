int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_005615a8[4];
extern int DAT_00587040[4];
int FUN_0019a120(void) {
    if (DAT_005615a8[0] == 0) {
        DAT_005615a8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005615a8[0];
}
