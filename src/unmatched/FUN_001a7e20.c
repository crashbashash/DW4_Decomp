int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00562258[4];
extern int DAT_00587040[4];
int FUN_001a7e20(void) {
    if (DAT_00562258[0] == 0) {
        DAT_00562258[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562258[0];
}
