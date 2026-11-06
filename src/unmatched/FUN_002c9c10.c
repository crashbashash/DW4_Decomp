int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00586828[4];
extern int DAT_00587040[4];
int FUN_002c9c10(void) {
    if (DAT_00586828[0] == 0) {
        DAT_00586828[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00586828[0];
}
