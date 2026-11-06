int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00562220[4];
extern int DAT_00587040[4];
int FUN_001a7780(void) {
    if (DAT_00562220[0] == 0) {
        DAT_00562220[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562220[0];
}
