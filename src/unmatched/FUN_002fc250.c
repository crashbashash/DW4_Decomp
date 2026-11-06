int InternalObjectList_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00587040[4];
extern int DAT_00587188[4];
int FUN_002fc250(void) {
    if (DAT_00587188[0] == 0) {
        DAT_00587188[0] = InternalObjectList_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00587188[0];
}
