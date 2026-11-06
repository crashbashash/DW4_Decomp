int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00560f10[4];
extern int DAT_00587040[4];
int FUN_00186c40(void) {
    if (DAT_00560f10[0] == 0) {
        DAT_00560f10[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00560f10[0];
}
