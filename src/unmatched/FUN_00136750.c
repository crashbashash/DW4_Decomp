int igMetaObject_Create();
int Memory_GetAllocatorBySelector();
extern int DAT_0055f088[4];
extern int DAT_00587040[4];
int FUN_00136750(void) {
    if (DAT_0055f088[0] == 0) {
        DAT_0055f088[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f088[0];
}
