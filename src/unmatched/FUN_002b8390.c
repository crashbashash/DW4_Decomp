int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00585828[4];
extern int DAT_00587040[4];
int FUN_002b8390(void) {
    if (DAT_00585828[0] == 0) {
        DAT_00585828[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00585828[0];
}
