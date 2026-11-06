int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_005867c8[4];
extern int DAT_00587040[4];
int FUN_002c8ca0(void) {
    if (DAT_005867c8[0] == 0) {
        DAT_005867c8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005867c8[0];
}
