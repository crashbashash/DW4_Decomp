int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00586120[4];
extern int DAT_00587040[4];
int FUN_002c3440(void) {
    if (DAT_00586120[0] == 0) {
        DAT_00586120[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00586120[0];
}
