int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_005612b0[4];
extern int DAT_00587040[4];
int FUN_00196190(void) {
    if (DAT_005612b0[0] == 0) {
        DAT_005612b0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005612b0[0];
}
