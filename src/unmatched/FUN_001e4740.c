int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00562ba0[4];
extern int DAT_00587040[4];
int FUN_001e4740(void) {
    if (DAT_00562ba0[0] == 0) {
        DAT_00562ba0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562ba0[0];
}
