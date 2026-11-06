int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00561450[4];
extern int DAT_00587040[4];
int FUN_00197af0(void) {
    if (DAT_00561450[0] == 0) {
        DAT_00561450[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00561450[0];
}
